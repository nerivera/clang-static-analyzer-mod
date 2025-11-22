set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyCaltechCSModule
  CaltechCSTidyModule.cpp
  MacroUsageCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangSerialization
  clangTidy
  clangTidyMiscModule
  clangTidyModernizeModule
  clangTidyReadabilityModule
  clangTidyUtils
  clangTooling
  )
