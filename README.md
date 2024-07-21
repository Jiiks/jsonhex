# jsonhex

Basic support for hex values with https://github.com/nlohmann/json

Currently only supports reading and all values are `uint64_t`

Usage:

```cpp
#include "jsonhex.hpp"

// Instead of using
std::ifstream f(path);
auto data = nlohmann::json::parse(output);

// use
auto data = jsonhex::parse(path);

// done
```

Supports hex values anywhere so for example the following:
```json
{
  "hexvalue": 0xDE0B6B3A763FFFF,
  "hexarr": [ "0xAE", "0x50" ]
}
```

Would be parsed to:
```cpp
struct ParseMe {
  uint64_t HexValue; // 999999999999999999
  vector<uint64_t> HexArr; // [174, 80]
}

auto data = jsonhex::parse(path);
ParseMe p{};
data.at("hexvalue").get_to(p.HexValue);
data.at("hexarr").get_to(p.HexArr);
```

TODO
- Serializing
- Support for other types maybe
