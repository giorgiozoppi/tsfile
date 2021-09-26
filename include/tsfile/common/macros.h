#ifndef IOTDB_NATIVE_MACROS_H
#define IOTDB_NATIVE_MACROS_H
#ifndef IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN
#define IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;            \
  void operator=(const TypeName&) = delete
#endif

#ifndef IOTDB_NATIVE_DEFAULT_MOVE_AND_ASSIGN
#define IOTDB_NATIVE_DEFAULT_MOVE_AND_ASSIGN(TypeName) \
  TypeName(TypeName&&) = default;               \
  TypeName& operator=(TypeName&&) = default
#endif
#endif
