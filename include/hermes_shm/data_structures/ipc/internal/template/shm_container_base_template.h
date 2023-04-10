public:
/**====================================
 * Variables & Types
 * ===================================*/
hipc::allocator_id_t alloc_id_;

/**====================================
 * Constructors
 * ===================================*/

/** Default constructor. Deleted. */
CLASS_NAME() = delete;

/** Move constructor. Deleted. */
CLASS_NAME(CLASS_NAME &&other) = delete;

/** Copy constructor. Deleted. */
CLASS_NAME(const CLASS_NAME &other) = delete;

/** Initialize container */
void shm_init_container(hipc::Allocator *alloc) {
  alloc_id_ = alloc->GetId();
}

/**====================================
 * Destructor
 * ===================================*/

/** Destructor. */
HSHM_ALWAYS_INLINE ~CLASS_NAME() = default;

/** Destruction operation */
HSHM_ALWAYS_INLINE void shm_destroy() {
  if (IsNull()) { return; }
  shm_destroy_main();
  SetNull();
}

/**====================================
 * Serialization
 * ===================================*/

/** Serialize into a Pointer */
HSHM_ALWAYS_INLINE void shm_serialize(
  hipc::Pointer &ar) const {
  auto &alloc = GetAllocator();
  ar = alloc->template
    Convert<CLASS_NAME, hipc::Pointer>(this);
}

/** Serialize into an AtomicPointer */
HSHM_ALWAYS_INLINE void shm_serialize(
  hipc::AtomicPointer &ar) const {
  auto &alloc = GetAllocator();
  ar = alloc->template
    Convert<CLASS_NAME, hipc::Pointer>(this);
}

/**====================================
 * Deserialization
 * ===================================*/

/** Deserialize from a Pointer */
static HSHM_ALWAYS_INLINE CLASS_NAME* shm_deserialize(
  const hipc::Pointer &ar) {
  auto &alloc = HERMES_MEMORY_REGISTRY_REF.GetAllocator(ar.allocator_id_);
  return alloc->Convert<CLASS_NAME, hipc::Pointer>(ar.ToOffsetPointer());
}

/** Deserialize from an AtomicPointer */
static HSHM_ALWAYS_INLINE CLASS_NAME* shm_deserialize(
  const hipc::AtomicPointer &ar) {
  auto &alloc = HERMES_MEMORY_REGISTRY_REF.GetAllocator(ar.allocator_id_);
  return alloc->Convert<CLASS_NAME, hipc::Pointer>(ar.ToOffsetPointer());
}

/**====================================
 * Header Operations
 * ===================================*/

/** Get a typed pointer to the object */
template<typename POINTER_T>
HSHM_ALWAYS_INLINE POINTER_T GetShmPointer() const {
  return GetAllocator()->template Convert<TYPED_CLASS, POINTER_T>(this);
}

/**====================================
 * Query Operations
 * ===================================*/

/** Get the allocator for this container */
HSHM_ALWAYS_INLINE hipc::Allocator* GetAllocator() const {
  return HERMES_MEMORY_REGISTRY_REF.GetAllocator(alloc_id_);
}

/** Get the shared-memory allocator id */
HSHM_ALWAYS_INLINE hipc::allocator_id_t& GetAllocatorId() const {
  return GetAllocator()->GetId();
}