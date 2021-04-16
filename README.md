### build: in root dir:
## cmake ./ && make
## cmake ./ && make
### run:
### run:
## ./Compiler input-filename [_dot-output-filename_ OR _run_]
## ./Compiler input-filename [run/ast/scope] [_dot-output-filename_ if ast]
##
##
### if you have graphviz(dot) installed:
### test print ast:
## ./test_tree.sh
## ./test_ast.sh
### and you can see cool derevya in .png format in tests/tree_making
### test print scope tree:
## ./test_scope.sh