/*
 * Copyright 2019 IBM Corp. and others
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.hpp"
#include "thread.hpp"
#include "wassert.hpp"

#include <memory>
#include <string>
#include <vector>

#include "wabt/src/option-parser.h"

namespace winter {

struct Options {
    std::string modulePath;
};

} // namespace winter

static winter::Options parseOptions(int argc, char** argv) {
    winter::Options options;

    wabt::OptionParser parser("winter-interp", "   executes a WebAssembly module\n");

    parser.AddArgument("filename",
                       wabt::OptionParser::ArgumentCount::One,
                       [&options](char const* arg) { options.modulePath = arg; });

    parser.Parse(argc, argv);

    return options;
}

static int ProgramMain(const winter::Options& options) {
    std::vector<uint8_t> data_buffer;

    auto result = wabt::ReadFile(options.modulePath, &data_buffer);
    WASSERT(result == wabt::Result::Ok, "Failed to load data from file");

    winter::Environment env;
    winter::Module module(
        winter::AbstractModule::parse(data_buffer.data(), data_buffer.size()),
        env
    );
    auto instance = winter::ModuleInstance::instantiate(module, winter::ImportEnvironment());

    winter::Thread thread;

    for (const winter::Export& e : instance->exports()) {
        if (e.type != winter::ExportType::Func)
            break;

        thread.execute(instance->funcs()[e.idx], {});
    }

    return 0;
}

int main(int argc, char** argv) {
    auto options = parseOptions(argc, argv);
    return ProgramMain(options);
}
