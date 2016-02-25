//===--- RedundantControlFlowCheck.h - clang-tidy----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_REDUNDANT_CONTROL_FLOW_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_REDUNDANT_CONTROL_FLOW_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace readability {

/// Eliminates redundant `return` statements at the end of a function that
/// returns `void`.
///
/// Eliminates redundant `continue` statements at the end of a loop body.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-control-flow.html
class RedundantControlFlowCheck : public ClangTidyCheck {
public:
  RedundantControlFlowCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  void
  checkRedundantReturn(const ast_matchers::MatchFinder::MatchResult &Result,
                       const CompoundStmt *Block);

  void
  checkRedundantContinue(const ast_matchers::MatchFinder::MatchResult &Result,
                         const CompoundStmt *Block);

  void issueDiagnostic(const ast_matchers::MatchFinder::MatchResult &Result,
                       const CompoundStmt *Block, const SourceRange &StmtRange,
                       const char *Diag);
};

} // namespace readability
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_REDUNDANT_CONTROL_FLOW_H