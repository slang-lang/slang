Runtime::AtomicValue:
- removed unused atomic type UINT
- introducted a pointer/reference to an object as new atomic type

Runtime::Object:
- replaced all usages of isNull() with isValid() and removed isNull() completely
- extracted From/ToJson functionality and re-implemented it in the extension methods FromJsonString(Object, string) and ToJsonString(Object, string)

Build system:
- extracted Json dependency from Core (and moved it to the correct targets (= executables))
- fixed adding additional link libraries by using an additional list (MODULES)

