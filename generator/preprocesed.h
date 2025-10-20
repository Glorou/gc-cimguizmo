
namespace ImGuizmo
{
             void SetDrawlist(ImDrawList* drawlist = nullptr);
             void BeginFrame();
             void SetImGuiContext(ImGuiContext* ctx);
             bool IsOver();
             bool IsUsing();
             void Enable(bool enable);
             void DecomposeMatrixToComponents(const float* matrix, float* translation, float* rotation, float* scale);
             void RecomposeMatrixFromComponents(const float* translation, const float* rotation, const float* scale, float* matrix);
             void SetRect(float x, float y, float width, float height);
             void SetOrthographic(bool isOrthographic);
             void DrawCubes(const float* view, const float* projection, const float* matrices, int matrixCount);
             void DrawGrid(const float* view, const float* projection, const float* matrix, const float gridSize);
   enum OPERATION
   {
      TRANSLATE_X = (1u << 0),
      TRANSLATE_Y = (1u << 1),
      TRANSLATE_Z = (1u << 2),
      ROTATE_X = (1u << 3),
      ROTATE_Y = (1u << 4),
      ROTATE_Z = (1u << 5),
      ROTATE_SCREEN = (1u << 6),
      SCALE_X = (1u << 7),
      SCALE_Y = (1u << 8),
      SCALE_Z = (1u << 9),
      BOUNDS = (1u << 10),
      SCALE_XU = (1u << 11),
      SCALE_YU = (1u << 12),
      SCALE_ZU = (1u << 13),
      TRANSLATE = TRANSLATE_X | TRANSLATE_Y | TRANSLATE_Z,
      ROTATE = ROTATE_X | ROTATE_Y | ROTATE_Z | ROTATE_SCREEN,
      SCALE = SCALE_X | SCALE_Y | SCALE_Z,
      SCALEU = SCALE_XU | SCALE_YU | SCALE_ZU,
      UNIVERSAL = TRANSLATE | ROTATE | SCALEU
   };
   inline OPERATION operator|(OPERATION lhs, OPERATION rhs)
   {
     return static_cast<OPERATION>(static_cast<int>(lhs) | static_cast<int>(rhs));
   }
   enum MODE
   {
      LOCAL,
      WORLD
   };
             bool Manipulate(const float* view, const float* projection, OPERATION operation, MODE mode, float* matrix, float* deltaMatrix = NULL, const float* snap = NULL, const float* localBounds = NULL, const float* boundsSnap = NULL);
             void ViewManipulate(float* view, float length, ImVec2 position, ImVec2 size, ImU32 backgroundColor);
             void ViewManipulate(float* view, const float* projection, OPERATION operation, MODE mode, float* matrix, float length, ImVec2 position, ImVec2 size, ImU32 backgroundColor);
             void SetID(int id);
             bool IsOver(OPERATION op);
             void SetGizmoSizeClipSpace(float value);
             void AllowAxisFlip(bool value);
}
struct ImDrawList;
struct ImRect;
namespace ImSequencer
{
   enum SEQUENCER_OPTIONS
   {
      SEQUENCER_EDIT_NONE = 0,
      SEQUENCER_EDIT_STARTEND = 1 << 1,
      SEQUENCER_CHANGE_FRAME = 1 << 3,
      SEQUENCER_ADD = 1 << 4,
      SEQUENCER_DEL = 1 << 5,
      SEQUENCER_COPYPASTE = 1 << 6,
      SEQUENCER_EDIT_ALL = SEQUENCER_EDIT_STARTEND | SEQUENCER_CHANGE_FRAME
   };
   struct SequenceInterface
   {
      bool focused = false;
      virtual int GetFrameMin() const = 0;
      virtual int GetFrameMax() const = 0;
      virtual int GetItemCount() const = 0;
      virtual void BeginEdit(int ) {}
      virtual void EndEdit() {}
      virtual int GetItemTypeCount() const { return 0; }
      virtual const char* GetItemTypeName(int ) const { return ""; }
      virtual const char* GetItemLabel(int ) const { return ""; }
      virtual const char* GetCollapseFmt() const { return "%d Frames / %d entries"; }
      virtual void Get(int index, int** start, int** end, int* type, unsigned int* color) = 0;
      virtual void Add(int ) {}
      virtual void Del(int ) {}
      virtual void Duplicate(int ) {}
      virtual void Copy() {}
      virtual void Paste() {}
      virtual size_t GetCustomHeight(int ) { return 0; }
      virtual void DoubleClick(int ) {}
      virtual void CustomDraw(int , ImDrawList* , const ImRect& , const ImRect& , const ImRect& , const ImRect& ) {}
      virtual void CustomDrawCompact(int , ImDrawList* , const ImRect& , const ImRect& ) {}
       virtual ~SequenceInterface() = default;
   };
   struct SequenceInterfaceVTable
   {
      int(*GetFrameMin) (void* userdata);
      int(*GetFrameMax) (void* userdata);
      int(*GetItemCount) (void* userdata);
      void(*BeginEdit) (int index, void* userdata);
      void(*EndEdit) (void* userdata);
      int(*GetItemTypeCount)(void* userdata);
      const char* (*GetItemTypeName)(int typeIndex, void* userdata);
      const char* (*GetItemLabel)(int index, void* userdata);
      const char* (*GetCollapseFmt)(void* userdata);
      void (*Get)(int index, int** start, int** end, int* type, unsigned int* color, void* userdata);
      void (*Add)(int type, void* userdata);
      void (*Del)(int index, void* userdata);
      void (*Duplicate)(int index, void* userdata);
      void (*Copy)(void* userdata);
      void (*Paste)(void* userdata);
      size_t (*GetCustomHeight)(int index, void* userdata);
      void (*DoubleClick)(int index, void* userdata);
      void (*CustomDraw)(int index, ImDrawList* draw_list, const ImRect* rc, const ImRect* legendRect, const ImRect* clippingRect, const ImRect* legendClippingRect, void* userdata);
      void (*CustomDrawCompact)(int index, ImDrawList* draw_list, const ImRect* rc, const ImRect* clippingRect, void* userdata);
      void* userdata;
   };
   SequenceInterface* CreateSequencerInterface(const SequenceInterfaceVTable& table);
   void DestroySequenceInterface(SequenceInterface* ptr);
   bool Sequencer(SequenceInterface* sequence, int* currentFrame, bool* expanded, int* selectedEntry, int* firstFrame, int sequenceOptions);
}