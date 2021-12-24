#ifndef SBDD_H
#define SBDD_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "SBDD/binarynode.h"
#include "BinaryFunction/binaryfunction.h"
#include "BinaryOperation/BinaryOperationAnd/binaryoperationand.h"
#include "BinaryOperation/BinaryOperationOr/binaryoperationor.h"
#include "BinaryOperation/BinaryOperationNot/binaryoperationnot.h"

bool compare_nodes(const BinaryNode& first_node, const BinaryNode& secont_node);

/*
    SBDD(
            unsigned int level_input = 0,
            std::vector < unsigned int > function_indexes_input = 0,
            std::shared_ptr < BinaryNode > low_node = nullptr,
            std::shared_ptr < BinaryNode > high_node = nullptr
            );
    SBDD(
            unsigned int level_input = 0,
            std::vector < unsigned int > function_indexes_input = 0,
            std::vector < std::shared_ptr < BinaryNode > > nodes = std::vector < std::shared_ptr < BinaryNode > >(2)
            );
 */

struct SBDDStructureUnit
{
    unsigned int index;
    unsigned int level;
    std::vector < unsigned int > function_indexes;
    std::string variable_name;
    std::vector < unsigned int > children;
};

struct SBDDStructure
{
    std::vector < SBDDStructureUnit > units;
};

struct SatUnit
{
    std::string variable_name;
    bool value;
};

struct Sat
{
    std::vector < SatUnit > units;
};

#define SAT_ERROR_VALUE Sat()

class SBDD
{
public:
    SBDD();

    unsigned int GetFunctionsCount() const;
    SBDDStructure GetStructure() const;

    void Build(
            const std::vector < BinaryFunction > &functions
            );

    void Apply(
            const std::shared_ptr < AbstractBinaryOperation > &operation,
            const SBDD &other_sbdd
            );

    void Restrict(
            const std::string &variable,
            const bool &switch_node
            );

    unsigned int SatCount() const;

    Sat AnySat() const;

    std::vector < Sat > AllSat() const;

    void Simplify();

private:
    SBDDStructure getStructureRecirsively(const std::shared_ptr < BinaryNode > &node) const;

    bool member(
            const unsigned int &level,
            const std::vector < unsigned int > &function_indexes,
            const std::shared_ptr < BinaryNode > &low_node,
            const std::shared_ptr < BinaryNode > &high_node
            ) const;

    std::shared_ptr < BinaryNode > lookup(
            const unsigned int &level,
            const std::vector < unsigned int > &function_indexes,
            const std::shared_ptr < BinaryNode > &low_node,
            const std::shared_ptr < BinaryNode > &high_node
            ) const;

    std::shared_ptr < BinaryNode > insert(
            const std::string &variable_name,
            const unsigned int &level,
            const std::vector < unsigned int > &function_indexes,
            const std::shared_ptr < BinaryNode > &low_node,
            const std::shared_ptr < BinaryNode > &high_node
            );

    std::shared_ptr < BinaryNode > buildRecursively(
            const BinaryFunction &function,
            const unsigned int &function_index,
            const unsigned int &level_index
            );

    std::shared_ptr < BinaryNode > applyRecursively(
            const std::shared_ptr < AbstractBinaryOperation > &operation,
            const std::shared_ptr < BinaryNode > &left_operand,
            const std::shared_ptr < BinaryNode > &right_operand,
            std::map <
                std::pair < std::shared_ptr < BinaryNode >, std::shared_ptr < BinaryNode > >,
                std::shared_ptr < BinaryNode >
            > &operation_results
            );

    std::shared_ptr < BinaryNode > restrictRecursively(
            const std::shared_ptr < BinaryNode > &node,
            const unsigned int &level_index,
            const bool &switch_node
            );

    unsigned int satCountRecursively(
            const std::shared_ptr < BinaryNode > &node
            ) const;

    Sat anySatRecursively(
            const std::shared_ptr < BinaryNode > &node
            ) const;

    std::vector < Sat > allSatRecursively(
            const std::shared_ptr < BinaryNode > &node
            ) const;

    std::shared_ptr < BinaryNode > simplifyRecursively(
            const std::shared_ptr < BinaryNode > &node1,
            const std::shared_ptr < BinaryNode > &node2
            );

    std::shared_ptr < BinaryNode > MakeNode(
            const std::string &variable_name,
            const unsigned int &level,
            const std::vector < unsigned int > &function_indexes,
            const std::shared_ptr < BinaryNode > &low_node,
            const std::shared_ptr < BinaryNode > &high_node
            );

    std::vector < std::vector < std::shared_ptr < BinaryNode > > > functions_nodes;
    std::vector < std::shared_ptr < BinaryNode > > functions_root_nodes;
    std::vector < std::shared_ptr < BinaryNode > > nodes;

    static const int terminal_0_node_index = 0;
    static const int terminal_1_node_index = 1;
};

#endif // SBDD_H
