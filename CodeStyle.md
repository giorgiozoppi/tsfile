# Code Style

Regarding the naming we use the Google C++ Code Style Guidelines. Please look at (https://google.github.io/styleguide/cppguide.html#General_Naming_Rules), with the following exceptions:

- Iterator and custom smart pointer shall use the STL snake case.
- One top-level namespace for public interfaces per project. Ensure uniqueness of namespaces via a common database. 
So no introduce namespaces until it's specifically agreed with other devs.
 