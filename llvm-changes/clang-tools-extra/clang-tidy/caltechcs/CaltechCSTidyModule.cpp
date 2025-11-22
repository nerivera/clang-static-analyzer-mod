//===-- CaltechCSTidyModule.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "MacroUsageCheck.h"

namespace clang {
namespace tidy {
namespace caltechcs {

/// A module containing checks of the Caltech CS Guidelines
class CaltechCSModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<MacroUsageCheck>(
        "caltechcs-macro-usage");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    ClangTidyOptions::OptionMap &Opts = Options.CheckOptions;

    return Options;
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<CaltechCSModule>
    X("caltechcs-module", "Adds checks for the Caltech CS Guidelines.");

} // namespace caltechcs

// This anchor is used to force the linker to link in the generated object file
// and thus register the CaltechCSModule.
volatile int CaltechCSModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
