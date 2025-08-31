
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
   enum COLOR
   {
      DIRECTION_X,
      DIRECTION_Y,
      DIRECTION_Z,
      PLANE_X,
      PLANE_Y,
      PLANE_Z,
      SELECTION,
      INACTIVE,
      TRANSLATION_LINE,
      SCALE_LINE,
      ROTATION_USING_BORDER,
      ROTATION_USING_FILL,
      HATCHED_AXIS_LINES,
      TEXT,
      TEXT_SHADOW,
      COUNT
   };
   struct Style
   {
                Style();
      float TranslationLineThickness;
      float TranslationLineArrowSize;
      float RotationLineThickness;
      float RotationOuterLineThickness;
      float ScaleLineThickness;
      float ScaleLineCircleSize;
      float HatchedAxisLineThickness;
      float CenterCircleSize;
      ImVec4 Colors[COLOR::COUNT];
   };
             Style& GetStyle();
}