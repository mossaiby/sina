# Design rationals

## Kernel

- Default types for scalar data and indices (`double` as `scalar_t` and `std::size_t` for `index_t`, respectively) are defined in `sina.h`. This should help avoiding to define such parameters for every object, reducing compile time and code complexity greatly.

- `vector` and `matrix` classes are designed as simple as possible. No overloaded mathematical operators, etc. Required operations will be defined on the go as separate functions, to avoid making intermediate variables that kill performance.

- A `node` object is assumed to contain the coordinates only, hence is inherited from `static_container`. Other properties will be stored in respective containers. This means that we are preferring *structure of arrays* over *array of structures* (the latter is the case in many OO based FEM codes). This will help increase the performance in certain operations due to less cache misses. Other methods will be added as soon as they are needed.

- A `node_set` object will contain a set of nodes.

- A `dof` object will contain the type and index of a single degree of freedom of a certain node, such as the nodes in the problem as well as its boundary condition.

- A `dof_set` object will contain a set of dofs. In general, nodes can have different sets of degrees of freedom, and this can only be determined at run time. Hence, `dof_set` is inherited from `dynamic_container`.

- The `process` class defines a base class for user-defined processes.

- The `application` class defines the base for an application.

## FEM

- The class `element` serves as the base for all elements, so that all kind of elements can be stored in a single container. `element_template` defines the basic functionality that must be implemented by an element.

- Each element defines, locally, the set of temporary variables it needs for elemental calculations. This should help greatly reduce the number of memory reallocations, as the size of these vectors / matrices remains the same, and the `vector` and `matrix` classes are smart enough to avoid memory reallocation in such cases.

- Currently, only nodally varying body force is implemented.

- `scm_*` classes will implement various types of SCM elements.

## I/O

- `stl` class can parse both ascii and binary STL files.

## To do:

- Integrate tractions in `calculate_rhs`.

- Typical SCM element with given order of shape functions and quadrature.

# Namespace and class map of **sina**

```
sina
  kernel
    vector
    matrix
    sparse_vector (*)
    sparse_matrix (*)
    linear_solver (*)

    static_container
    dynamic_container

    reference_wrapper

    properties
      constant_properties
      variable_properties

    node
    node_set

    dof
    dof_set
    
    quadrature
  fem
    element
      element_template
    element_set
  strategy
    explicit_central_difference_dynamic_fem
  process
    determine_nodal_dofs
  application
  io
    stl
  utils
  misc
    stl
    mathematica
```

### Notes:

- Classes marked with (*) will not be implemented until there is a use case for them.
- Classes marked with (-) are unused in current design and are to be deleted soon.


# Logo of sina and common header for all files:

```
        _             
    ___(_)_ __   __ _ 
   / __| | '_ \ / _` |    simple and intuitive numerical analysis
   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved

   version: major.minor.patch

//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// filename.ext
//
// file purpose
//         
```