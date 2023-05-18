#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

class ForStmtVisitor : public RecursiveASTVisitor<ForStmtVisitor> {
public:
    bool VisitForStmt(ForStmt* stmt) {
        if (stmt->getBody()) {
            for (const Stmt* S = stmt->getBody(); S; S = S->getSuccessorStmt()) {
                if (isa<BreakStmt>(S)) {
                    llvm::outs() << "Найден оператор break в цикле for\n";
                }
                else if (isa<ContinueStmt>(S)) {
                    llvm::outs() << "Найден оператор continue в цикле for\n";
                }
            }
        }
        return true;
    }
};

class ForStmtASTConsumer : public ASTConsumer {
public:
    virtual void HandleTranslationUnit(ASTContext& Context) {
        ForStmtVisitor Visitor;
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }
};

class ForStmtFrontendAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& Compiler, StringRef InFile) {
        return std::make_unique<ForStmtASTConsumer>();
    }
};

int main(int argc, const char** argv) {
    if (argc > 1) {
        clang::tooling::runToolOnCode(std::make_unique<ForStmtFrontendAction>(), argv[1]);
    }
    return 0;
}