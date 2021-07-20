# vepp
Simple, tested, header only vector template for C++11

This is a very simple template for dealing with N dimensional vectors. The
dimension is fixed at compile time to decrease the friction of usage for
CUDA-C and OpenCL like APIs.

It has a very C like usage. General usage would be something like:

```c++
#include "vepp.hpp"

int main(){

  // define object
  vepp::VecN<real, 5> v(1);

  // define output
  std::vector<real> out;

  // immutable method call, ie v does not change as a result of this operation
  auto result = v.add(1, out).status;

  // check status
  if (result == vepp::SUCCESS){
      // do further processing
      std::cout << out[0] << std::endl;
      std::cout << out[1] << std::endl;
      std::cout << out[2] << std::endl;
      std::cout << out[3] << std::endl;
      std::cout << out[4] << std::endl;
  }else{
      return -1;
  }
  return 0;
}

```

We have tested all the public methods. All methods return a result object.
`Result` object contains essentially two things:

- Operation status
- Debugging information

You can check the operation status by simply accessing to the `status`
property of the object. It can be any of the following:
```c++
enum status_t : std::uint8_t {
  SUCCESS = 1,
  SIZE_ERROR = 2,
  INDEX_ERROR = 3,
  ARG_ERROR = 4,
  NOT_CALLED = 5,
  NOT_IMPLEMENTED = 6
};
```

`INDEX_ERROR` signals an illegal access or set to a position which is
not covered by the current vector.

`SIZE_ERROR` signals an illegal usage of arguments whose sizes are not adapted to
demanded operation.

`ARG_ERROR` signals an illegal usage of arguments that is not related to size.
For example a zero division would be considered as an `ARG_ERROR`.

`NOT_CALLED` signals that the `Result` object does not result from a method
call.

`NOT_IMPLEMENTED` signals that the method has not been implemented yet.


All functions except `set` are qualified by `const`.
As long as you don't call set anywhere you won't be modifying the created
objects. We also provide several wrapper functions to ease of usage. Notably
the `CHECK` function takes in a `Result` object and outputs a boolean value.
The intended usage would be something like:

```c++
#include "vepp.hpp"

int main(){
  VecN<real, 2> v;
  unsigned int vsize = 5;
  bool vflag = CHECK(v.size(vsize));
  std::cout << vflag << std::endl;
  // true

  return 0;
}

```
There are also `INFO` and `INFO_VERBOSE`. Their usage is mostly the same, with
the exception that they output a result object rather than a boolean.
