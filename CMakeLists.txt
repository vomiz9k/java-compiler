cmake_minimum_required(VERSION 3.16)




project(Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -Wall)

set(CURRENT_EXECUTABLE "${PROJECT_NAME}")
set(IR_LIB "${PROJECT_NAME}IrLib")

set(
    HEADERS
    ${Compiler_SOURCE_DIR}/driver/driver.hpp
    ${Compiler_SOURCE_DIR}/bison/bison.hpp
    ${Compiler_SOURCE_DIR}/lexer/lexer.hpp
    ${Compiler_SOURCE_DIR}/nterms/big_include.hpp
    ${Compiler_SOURCE_DIR}/nterms/base/base.hpp
    ${Compiler_SOURCE_DIR}/visitor/visitor.hpp
    ${Compiler_SOURCE_DIR}/friends_visitors/friends_visitors
    ${Compiler_SOURCE_DIR}/scope/base_scope.hpp
    ${Compiler_SOURCE_DIR}/scope/base_symbol.hpp

        function-mechanisms/address/Address.h
        function-mechanisms/address/AddressInFrame.h
        function-mechanisms/address/AddressInRegister.h
)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(
    MyParser
    ${Compiler_SOURCE_DIR}/bison/bison.y
    ${Compiler_SOURCE_DIR}/bison/bison.cpp
    DEFINES_FILE ${Compiler_SOURCE_DIR}/bison/bison.hpp
)


FLEX_TARGET(
    MyScanner
    ${Compiler_SOURCE_DIR}/lexer/lexer.l
    ${Compiler_SOURCE_DIR}/lexer/lexer.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


add_subdirectory(irtree)

add_executable(
    Compiler
    main.cpp

    ${Compiler_SOURCE_DIR}/driver/driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
    ${Compiler_SOURCE_DIR}/nterms/assignment/assignment.cpp
    ${Compiler_SOURCE_DIR}/nterms/class_declarations/class_declarations.cpp
    ${Compiler_SOURCE_DIR}/nterms/class_declaration/class_declaration.cpp
    ${Compiler_SOURCE_DIR}/nterms/declarations/declarations.cpp
    ${Compiler_SOURCE_DIR}/nterms/expression/expression.cpp
    ${Compiler_SOURCE_DIR}/nterms/expressions/expressions.cpp
    ${Compiler_SOURCE_DIR}/nterms/field_invocation/field_invocation.cpp
    ${Compiler_SOURCE_DIR}/nterms/main_class/main_class.cpp
    ${Compiler_SOURCE_DIR}/nterms/method_arg/method_arg.cpp
    ${Compiler_SOURCE_DIR}/nterms/method_args/method_args.cpp
    ${Compiler_SOURCE_DIR}/nterms/method_invocation/method_invocation.cpp
    ${Compiler_SOURCE_DIR}/nterms/program/program.cpp
    ${Compiler_SOURCE_DIR}/nterms/statement/statement.cpp
    ${Compiler_SOURCE_DIR}/nterms/statements/statements.cpp
    ${Compiler_SOURCE_DIR}/nterms/type/type.cpp
    ${Compiler_SOURCE_DIR}/nterms/value/value.cpp
    ${Compiler_SOURCE_DIR}/nterms/declaration/declaration.cpp
    ${Compiler_SOURCE_DIR}/nterms/body/body.cpp
    ${Compiler_SOURCE_DIR}/nterms/variable_declaration/variable_declaration.cpp
    ${Compiler_SOURCE_DIR}/nterms/method_declaration/method_declaration.cpp

    ${Compiler_SOURCE_DIR}/visitor/gv_visitor.cpp
    ${Compiler_SOURCE_DIR}/visitor/optimization_visitor.cpp
    ${Compiler_SOURCE_DIR}/visitor/delete_visitor.cpp
    ${Compiler_SOURCE_DIR}/visitor/interpreter_visitor.cpp
    ${Compiler_SOURCE_DIR}/visitor/symbol_table_visitor.cpp

    ${Compiler_SOURCE_DIR}/symbols/base_symbol.cpp
    ${Compiler_SOURCE_DIR}/symbols/class_symbol.cpp
    ${Compiler_SOURCE_DIR}/symbols/variable_symbol.cpp
    ${Compiler_SOURCE_DIR}/symbols/method_symbol.cpp
    visitor/ir_tree_visitor.cpp visitor/ir_tree_visitor.hpp


        function-mechanisms/address/AddressInFrame.cpp
        function-mechanisms/address/AddressInRegister.cpp
)

target_include_directories(Compiler PUBLIC
    ${Compiler_SOURCE_DIR}/driver
    ${Compiler_SOURCE_DIR}/bison
    ${Compiler_SOURCE_DIR}/lexer
    ${Compiler_SOURCE_DIR}/visitor
    ${Compiler_SOURCE_DIR}/nterms
    ${Compiler_SOURCE_DIR}/nterms/base
    ${Compiler_SOURCE_DIR}/friends_visitors
    ${Compiler_SOURCE_DIR}/scope
    ${Compiler_SOURCE_DIR}/symbols
    ${Compiler_SOURCE_DIR}
)

target_link_libraries(${CURRENT_EXECUTABLE} ${IR_LIB})




