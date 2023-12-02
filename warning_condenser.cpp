/*

[build command] > out.txt 2>&1
build command can be make, cmake, a direct gcc,g++,clang,clang++ line, etc.

*/

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <cassert>
#include <map>

std::vector<std::string> read_text_file_into_vector(const std::string& filepath_)
{
    std::vector<std::string> lines;
    std::ifstream input_file;
    input_file.open(filepath_);
    assert(input_file);

    for (std::string line; std::getline(input_file, line); /**/) {
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    // /home/linux/tests/kuzu_dev/kuzu/third_party/miniparquet/src/thrift/transport/TTransportException.h:65:85: warning:

#if 0
    std::vector<std::string> warnings = read_text_file_into_vector(R"(D:\temp\__warning_condenser\gcc.build.txt)");
#endif

#if 1
    std::vector<std::string> warnings = read_text_file_into_vector(R"(D:\temp\__warning_condenser\clang.build.txt)");
#endif

#if 0
    std::vector<std::string> warnings
    {
R"(/home/linux/tests/kuzu_dev/kuzu/third_party/miniparquet/src/thrift/transport/TTransportException.h:65:85: warning: unused parameter 'errno_copy' [-Wunused-parameter])",
R"(   65 |   TTransportException(TTransportExceptionType type, const std::string& message, int errno_copy))",
R"(      |                                                                                     ^)",
R"(1 warning generated.)",
R"(/home/linux/tests/kuzu_dev/kuzu/third_party/miniz/miniz.cpp:3161:76: warning: unused parameter 'pArray' [-Wunused-parameter])",
R"( 3161 | static MZ_FORCEINLINE mz_uint mz_zip_array_range_check(const mz_zip_array *pArray, mz_uint index))",
R"(      |                                                                            ^)",
R"(/home/linux/tests/kuzu_dev/kuzu/third_party/miniz/miniz.cpp:5998:120: warning: unused parameter 'last_modified' [-Wunused-parameter])",
R"( 5998 |                                     mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32, MZ_TIME_T *last_modified,)",
R"(      |                                                                                                                        ^)",
R"(2 warnings generated.)",
R"([  0%] Building CXX object third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc_wrapper.cpp.o)",
R"([  1%] Building CXX object third_party/miniparquet/CMakeFiles/miniparquet.dir/src/parquet/parquet_types.cpp.o)",
R"(In file included from /home/linux/tests/kuzu_dev/kuzu/third_party/re2/bitstate.cpp:29:)",
R"(In file included from /home/linux/tests/kuzu_dev/kuzu/third_party/re2/include/prog.h:23:)",
R"(/home/linux/tests/kuzu_dev/kuzu/third_party/re2/include/sparse_array.h:231:36: warning: unused parameter 'min' [-Wunused-parameter])",
R"(  231 |     void MaybeInitializeMemory(int min, int max) {)",
R"(      |                                    ^)",
R"(/home/linux/tests/kuzu_dev/kuzu/third_party/re2/include/sparse_array.h:231:45: warning: unused parameter 'max' [-Wunused-parameter])",
R"(  231 |     void MaybeInitializeMemory(int min, int max) {)",
R"(      |                                             ^)",
R"(In file included from /home/linux/tests/kuzu_dev/kuzu/third_party/re2/bitstate.cpp:29:)"
    };
#endif

    struct warning_info_t
    {
        size_t log_line{};
        std::string full;
        std::string path;
        size_t line{};
        size_t row{};
        std::string msg;
        std::string type;

        std::vector<std::string> diag_line;
        std::string full_diag;
    };

    std::vector<warning_info_t> warnings_info;

    // find warnings

    const std::regex warning_regex(R"(^(/.*?)\:(\d+)\:(\d+)\: warning\: (.*?)\[([^ ]*?)\]$)");
    for (size_t i = 0; i < warnings.size(); ++i)
    {
        const auto& line = warnings[i];
        //printf("%s\n", line.c_str());
        std::smatch match;
        if (std::regex_match(line, match, warning_regex))
        {
            assert(match.size() == 6);
            const std::string full = match[0];
            const std::string path = match[1];
            const size_t line = std::stoi(match[2]);
            const size_t row = std::stoi(match[3]);
            const std::string msg = match[4];
            const std::string type = match[5];
            //printf("%s\n", line.c_str());

            warnings_info.push_back({ i, full, path, line, row, msg, type });
        }
    }

    // get diagnostic lines

    for (auto& wi : warnings_info)
    {
        //printf("line: %zu\n  file: %s\n  at: %zu/%zu\n  msg: %s\n  type: %s\n", wi.log_line, wi.path.c_str(), wi.line, wi.row, wi.msg.c_str(), wi.type.c_str());

        /*
/home/linux/tests/kuzu_dev/kuzu/third_party/re2/compile.cpp:787:35: warning: unused parameter 're' [-Wunused-parameter]
  787 | Frag Compiler::ShortVisit(Regexp* re, Frag) {
      |                                   ^
/home/linux/tests/kuzu_dev/kuzu/third_party/re2/compile.cpp:793:33: warning: unused parameter 're' [-Wunused-parameter]
        */

        const std::regex diag_regex(R"(^\s+(\d+)*\s+\|.*?$)");
        for (size_t i = wi.log_line + 1; i < warnings.size(); ++i)
        {
            const std::string& line = warnings[i];
            std::smatch match;
            int brk = 1;
            if (std::regex_match(line, match, diag_regex))
            {
                //printf("%s\n", line.c_str());
                wi.diag_line.push_back(line);
                wi.full_diag += line + "\n";
            }
            else
            {
                break;
            }
        }
    }

    std::map<std::string, std::map<std::string, size_t>> type_map;

    for (auto& wi : warnings_info)
    {
        const std::string content = wi.path + ":" + std::to_string(wi.line) + ":" + std::to_string(wi.row) + ": " + wi.msg;

        auto& m = type_map[wi.type];

        auto it = m.find(content);
        if (it == m.end())
        {
            m[content] = 1;
        }
        else
        {
            ++m[content];
        }
    }

    //-----

    struct warning_count_t
    {
        size_t count{};
        std::string content;
    };

    struct type_info_t
    {
        std::string type;
        std::vector<warning_count_t> warnings;
    };

    std::vector<type_info_t> type_infos;
    for (auto& [k, v] : type_map)
    {
        type_info_t ti;
        ti.type = k;

        for (const auto& [k2, v2] : v)
        {
            ti.warnings.push_back({ v2, k2 });
        }

        type_infos.push_back(ti);
    }

    auto pred = [&](type_info_t& a, type_info_t& b) { return a.warnings.size() > b.warnings.size(); };
    std::sort(type_infos.begin(), type_infos.end(), pred);

    for (auto& ti : type_infos)
    {
        auto& warnings = ti.warnings;
        auto pred = [&](warning_count_t& a, warning_count_t& b) { return a.count > b.count; };
        std::sort(warnings.begin(), warnings.end(), pred);
    }

    //-----


    for (const auto& ti : type_infos)
    {
        printf("(count: % 5zu) type: %s\n", ti.warnings.size(), ti.type.c_str());

        for (const auto& wc : ti.warnings)
        {
            printf("  (% 5zu) %s\n", wc.count, wc.content.c_str());
        }
    }

    return 0;
}
