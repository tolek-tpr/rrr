#ifndef RRR_PIPELINE_HPP
#define RRR_PIPELINE_HPP
#include <string>
#include <vector>

namespace rrr {

    class RrrPipeline {
    public:
            RrrPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
    private:
            static std::vector<char> readFile(const std::string& filepath);

            void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
    };
}

#endif //RRR_PIPELINE_HPP
