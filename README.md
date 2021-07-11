# vepp
Simple, tested, header only vector library for C++11

It should be fairly easy to use and integrate into existing projects.
It has a very C like api design. You can safely wrap all function calls with a
debugging macro or code. For example:

```c++
#include <ostream>
#include <vector>
#include "vepp.hpp"

int main(){
  std::vector<float> vin;
  vin.resize(2);
  vin[0] = static_cast<float>(2);
  vin[1] = static_cast<float>(4);
  vepp::VecN<float, 2> v(vin);
  float c = 0.0f;
  vepp:VECN_ r = v.get(0, c);

  std::cout << c << std::endl;
  // 2.0

  std::cout << r << std::endl;
  // 1 which is true

  // trying to acces to an out of bounds index
  r = v.get(10, c);

  std::cout << r << std::endl;
  // false

  r = v.set(10, c);
  std::cout << r << std::endl;
  // false

  return 0;
}
```

Notice that we pass `2` as template parameter, so yes the `VecN` has a fixed
size determined at the compile time. Internally we are using `array` as a
container. This decreases the friction between `VecN` and APIs like CUDA-C,
OpenCL, etc. Nevertheless, the user can pass a `vector` to most methods of
`VecN`. If the size of the `vector` is not compatible with the operation we
return `SIZE_ERROR`.

As you might have guessed, we never throw exceptions. So `throw` does not
occur anywhere in code. No explicit use of `new` and `delete` either.
We don't resize output vectors if they are correctly sized as well. 
For example:

```c++
#include <ostream>
#include <vector>
#include "vepp.hpp"

int main(){

std::vector<float> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  vepp::VecN<real, 5> v(inv);

  // resized output vector
  std::vector<real> out;
  auto result_1 = v.add(1, out);

  // not resized output vector
  std::vector<real> nout;
  nout.resize(5);
  auto result_2 = v.add(1, nout);

  std::cout << result_1 << std::endl;
  // SUCCESS

  std::cout << result_2 << std::endl;
  // SUCCESS

  std::cout << out[0] << " - " << nout[0] << std::endl;
  // 2

  std::cout << out[1] << " - " << nout[1] << std::endl;
  // 3

  std::cout << out[2] << " - " << nout[2] << std::endl;
  // 4

  std::cout << out[3] << " - " << nout[3] << std::endl;
  // 3

  std::cout << out[4] << " - " << nout[4] << std::endl;
  // 2

  return 0;
}
```

We also provide 3 simple debugging macros for wrapping calls:

- `CHECK`: returns a boolean if the call outputs `SUCCESS` flag
- `INFO`: returns `VECN_FLAG` flag but shows out the file and line
  information if the call outputs an error flag.
- `INFO_VERBOSE`: returns `VECN_FLAG` flag but shows the file and line
  information if the call outputs an error flag, also shows success message.

Here is a usage example:

```c++
#include <ostream>
#include <vector>
#include "vepp.hpp"

int main(){
  std::vector<float> vin;
  vin.resize(2);
  vin[0] = static_cast<float>(2);
  vin[1] = static_cast<float>(4);
  vepp::VecN<float, 2> v(vin);
  float c = 0.0f;
  bool r = CHECK(v.get(0, c));

  std::cout << c << std::endl;
  // 2.0

  std::cout << r << std::endl;
  // true

  // trying to acces to an out of bounds index
  auto res = INFO(v.get(10, c));
  // INDEX_ERROR :: myfile.cpp :: 10

  res = INFO(v.set(10, c));
  // INDEX_ERROR :: myfile.cpp :: 10

  return 0;
}

```

