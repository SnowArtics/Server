// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Enum.pb.h"
#include "Struct.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Protocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocol_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocol_2eproto;
namespace Protocol {
class S_TEST;
struct S_TESTDefaultTypeInternal;
extern S_TESTDefaultTypeInternal _S_TEST_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::S_TEST* Arena::CreateMaybeMessage<::Protocol::S_TEST>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class S_TEST final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.S_TEST) */ {
 public:
  inline S_TEST() : S_TEST(nullptr) {}
  ~S_TEST() override;
  explicit constexpr S_TEST(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  S_TEST(const S_TEST& from);
  S_TEST(S_TEST&& from) noexcept
    : S_TEST() {
    *this = ::std::move(from);
  }

  inline S_TEST& operator=(const S_TEST& from) {
    CopyFrom(from);
    return *this;
  }
  inline S_TEST& operator=(S_TEST&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const S_TEST& default_instance() {
    return *internal_default_instance();
  }
  static inline const S_TEST* internal_default_instance() {
    return reinterpret_cast<const S_TEST*>(
               &_S_TEST_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(S_TEST& a, S_TEST& b) {
    a.Swap(&b);
  }
  inline void Swap(S_TEST* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(S_TEST* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline S_TEST* New() const final {
    return new S_TEST();
  }

  S_TEST* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<S_TEST>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const S_TEST& from);
  void MergeFrom(const S_TEST& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(S_TEST* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.S_TEST";
  }
  protected:
  explicit S_TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBuffsFieldNumber = 4,
    kIdFieldNumber = 1,
    kHpFieldNumber = 2,
    kAttackFieldNumber = 3,
  };
  // repeated .Protocol.BuffData buffs = 4;
  int buffs_size() const;
  private:
  int _internal_buffs_size() const;
  public:
  void clear_buffs();
  ::Protocol::BuffData* mutable_buffs(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
      mutable_buffs();
  private:
  const ::Protocol::BuffData& _internal_buffs(int index) const;
  ::Protocol::BuffData* _internal_add_buffs();
  public:
  const ::Protocol::BuffData& buffs(int index) const;
  ::Protocol::BuffData* add_buffs();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
      buffs() const;

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // uint32 hp = 2;
  void clear_hp();
  ::PROTOBUF_NAMESPACE_ID::uint32 hp() const;
  void set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_hp() const;
  void _internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 attack = 3;
  void clear_attack();
  ::PROTOBUF_NAMESPACE_ID::uint32 attack() const;
  void set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_attack() const;
  void _internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.S_TEST)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData > buffs_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 hp_;
  ::PROTOBUF_NAMESPACE_ID::uint32 attack_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// S_TEST

// uint64 id = 1;
inline void S_TEST::clear_id() {
  id_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 S_TEST::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 S_TEST::id() const {
  // @@protoc_insertion_point(field_get:Protocol.S_TEST.id)
  return _internal_id();
}
inline void S_TEST::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
}
inline void S_TEST::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.S_TEST.id)
}

// uint32 hp = 2;
inline void S_TEST::clear_hp() {
  hp_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 S_TEST::_internal_hp() const {
  return hp_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 S_TEST::hp() const {
  // @@protoc_insertion_point(field_get:Protocol.S_TEST.hp)
  return _internal_hp();
}
inline void S_TEST::_internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  hp_ = value;
}
inline void S_TEST::set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:Protocol.S_TEST.hp)
}

// uint32 attack = 3;
inline void S_TEST::clear_attack() {
  attack_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 S_TEST::_internal_attack() const {
  return attack_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 S_TEST::attack() const {
  // @@protoc_insertion_point(field_get:Protocol.S_TEST.attack)
  return _internal_attack();
}
inline void S_TEST::_internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  attack_ = value;
}
inline void S_TEST::set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_attack(value);
  // @@protoc_insertion_point(field_set:Protocol.S_TEST.attack)
}

// repeated .Protocol.BuffData buffs = 4;
inline int S_TEST::_internal_buffs_size() const {
  return buffs_.size();
}
inline int S_TEST::buffs_size() const {
  return _internal_buffs_size();
}
inline ::Protocol::BuffData* S_TEST::mutable_buffs(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.S_TEST.buffs)
  return buffs_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
S_TEST::mutable_buffs() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.S_TEST.buffs)
  return &buffs_;
}
inline const ::Protocol::BuffData& S_TEST::_internal_buffs(int index) const {
  return buffs_.Get(index);
}
inline const ::Protocol::BuffData& S_TEST::buffs(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.S_TEST.buffs)
  return _internal_buffs(index);
}
inline ::Protocol::BuffData* S_TEST::_internal_add_buffs() {
  return buffs_.Add();
}
inline ::Protocol::BuffData* S_TEST::add_buffs() {
  // @@protoc_insertion_point(field_add:Protocol.S_TEST.buffs)
  return _internal_add_buffs();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
S_TEST::buffs() const {
  // @@protoc_insertion_point(field_list:Protocol.S_TEST.buffs)
  return buffs_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
