/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file     QPSVisitor.h
 * @brief    
 * @author   Ivan Dario Jimenez
 * @date     3/5/16
 */

#pragma once

#include <gtsam_unstable/linear/QP.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/inference/Key.h>
#include <gtsam/base/Matrix.h>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/sequence.hpp>
#include <unordered_map>
#include <string>
#include <vector>

namespace gtsam {
/**
 * As the parser reads a file, it call functions in this visitor. This visitor in turn stores what the parser has read
 * in a way that can be later used to build the full QP problem in the file.
 */
class QPSVisitor {
private:
  typedef std::unordered_map<Key, Matrix11> coefficient_v;
  typedef std::unordered_map<std::string, coefficient_v> constraint_v;

  std::unordered_map<std::string, constraint_v*> row_to_constraint_v; // Maps QPS ROWS to Variable-Matrix pairs
  constraint_v E; // Equalities
  constraint_v IG;// Inequalities >=
  constraint_v IL;// Inequalities <=
  unsigned int numVariables;
  std::unordered_map<std::string, double> b; // maps from constraint name to b value for Ax = b equality constraints
  std::unordered_map<std::string, double> ranges; // Inequalities can be specified as ranges on a variable
  std::unordered_map<Key, Vector1> g; // linear term of quadratic cost
  std::unordered_map<std::string, Key> varname_to_key; // Variable QPS string name to key
  std::unordered_map<Key, std::unordered_map<Key, Matrix11> > H; // H from hessian
  double f; // Constant term of quadratic cost
  std::string obj_name; // the objective function has a name in the QPS
  std::string name_; // the quadratic program has a name in the QPS
  std::unordered_map<Key, double> up; // Upper Bound constraints on variable where X < MAX
  std::unordered_map<Key, double> lo; // Lower Bound constraints on variable where MIN < X
  std::unordered_map<Key, double> fx; // Equalities specified as FX in BOUNDS part of QPS
  std::vector<Key> Free; // Variables can be specified as Free (to which no constraints apply)
  const bool debug = false;

public:
  QPSVisitor() : numVariables(1) {
  }

  void setName(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>> const & name);

  void addColumn(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>> const & vars);

  void addColumnDouble(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, double, std::vector<char>,
          std::vector<char>, std::vector<char>, double> const & vars);

  void addRHS(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>> const & vars);

  void addRHSDouble(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>, std::vector<char>, std::vector<char>, double> const & vars);

  void addRangeSingle(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>> const & vars);

  void addRangeDouble(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>, std::vector<char>, std::vector<char>, double> const & vars);

  void addRow(
      boost::fusion::vector<std::vector<char>, char, std::vector<char>,
          std::vector<char>, std::vector<char>> const & vars);

  void addBound(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, double> const & vars);

  void addFreeBound(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>> const & vars);

  void addQuadTerm(
      boost::fusion::vector<std::vector<char>, std::vector<char>,
          std::vector<char>, std::vector<char>, std::vector<char>, double,
          std::vector<char>> const & vars);

  QP makeQP();
}
;
}
