// Components

struct Vector2 {
    float x, y;
};

struct Vector2i {
    int x, y;
};

struct Vector3i {
    int x, y, z;
};

using TimeType = int;

using Position = Vector2i;

using Orientation = float;

struct InitialPosition : Position { using Position::Position; };
struct StartPosition : Position { using Position::Position; };

struct Size : Position { using Position::Position; };
struct InitialSize : Size { using Size::Size; };

using Index = unsigned int;

struct Preselected {};
struct Selected {};
struct Hovered {};

struct Color {
    float r, g, b, a;
};

struct Name {
    const char* text;
};


// From e.g. Wacom tablet
struct InputPressure  { float strength; };
struct InputPitch  { float angle; };
struct InputYaw  { float angle; };


// From e.g. Mouse or WASD keys
struct InputPosition2D {
    Vector2i absolute;
    Vector2i relative;
    Vector2i delta;
    Vector2i normalised;
    unsigned int width;
    unsigned int height;
};

struct InputPosition3D : Vector3i {};

// From e.g. WASD keys or D-PAD on XBox controller
enum class Direction2D : std::uint8_t { Left = 0, Up, Right, Down };
enum class Direction3D : std::uint8_t { Left = 0, Up, Right, Down, Forward, Backward };



namespace Input {

    // All devices carry one of these
    struct Device {
        std::string_view id;
    };

    // Keep track of which device was active last
    struct LastUsedDevice {};

    // Keep track of which tool is assigned to a device
    struct AssignedTool {
        entt::entity entity { entt::null };
    };


    /**
     * @brief A mouse with 3 buttons and scroll wheel
     *
     *    _________
     *   /   _|_   \
     *  ||   | |   ||
     *  ||   |_|   ||
     *  ||____|____||
     *  |           |
     *  |           |
     *  |           |
     *  |           |
     *  |___________|
     *
     */
    struct MouseDevice {
        entt::entity lastPressed { entt::null };
        entt::entity lastHovered { entt::null };

        TimeType time { 0 };
        TimeType pressTime { 0 };
        TimeType releaseTime { 0 };

        Vector2i position { 0, 0 };
        Vector2 scroll { 0.0f, 0.0f };
        Vector2 velocity { 0.0f, 0.0f };
        Vector2 acceleration { 0.0f, 0.0f };

        enum Buttons : int {
            None         = 1 << 0,
            ButtonLeft   = 1 << 1,
            ButtonMiddle = 1 << 2,
            ButtonRight  = 1 << 3,
        };

        int buttons { None };

        bool pressed { false };
        bool released { false };
        bool dragging { false };
        bool changed { false };

        // Internal state
        std::map<TimeType, InputPosition2D> _positions;
        Vector2i _pressPosition { 0, 0 };
        Vector2i _lastPosition { 0, 0 };
        Vector2i _deltaPosition { 0, 0 };
    };


    /**
     * @brief A Wacom Intuos pen
     *
     */
    struct WacomPenDevice {
        entt::entity lastPressed { entt::null };
    };


    /**
     * @brief A Wacom Feel (tm) multi-touch device, with 10 fingers as 100hz
     *
     *      _ 
     *     | |
     *     | |
     *     | | _  _
     *     | |/ \/ \_
     *     |         \ 
     *    /|  ^   ^   |
     *   /            |
     *  |             |
     *  |             |
     *  |             |
     *   \           / 
     *    |         |
     *
     */
    struct WacomTouchDevice {
        entt::entity lastPressed { entt::null };
    };


    /**
     * @brief An XBox controller, or compatible alternative
     * 
     *     _____________
     *    / _           \
     *   / / \  o  o  _  \
     *  /  \_/       / \  \
     * /      +      \_/   \
     * |     _________     |
     *  \   /         \   /
     *   \_/           \_/
     * 
     */
    struct GamepadDevice {
        entt::entity lastPressed { entt::null };
    };
}


namespace Intent {

    struct Move {
        int x, y;
    };

    struct Rotate {
        int angle;
    };

    struct Scale {
        int scale;
    };


    struct SortTracks {};
}


namespace Tool {

    enum class Type : std::uint8_t {
        None = 0,
        Select,
        DragSelect,
        LassoSelect,

        Translate,
        Rotate,
        Scale,

        Scrub,
    };

    // Possible event types
    enum EventType : std::uint8_t {
        InvalidEvent = 0,  // Catch uninitialised types

        SelectEvent,
        LassoSelectEvent,
        DragSelectEvent,

        TranslateEvent,
        RotateEvent,
        ScaleEvent,

        ScrubEvent,
    };

    enum State : std::uint8_t {
        ToolState_None = 0,
        ToolState_Activated,
        ToolState_Active,
        ToolState_Deactivated
    };

    // Tool stage intentions
    struct SetupIntent {};
    struct BeginIntent {};
    struct UpdateIntent { int time; };
    struct PreviewIntent {};
    struct FinishIntent {};
    struct RecordIntent {};

    struct CanRecord {};

    // Tool mode intentions
    struct PrimaryIntent {};    // E.g. left mouse button
    struct SecondaryIntent {};  // E.g. right mouse button
    struct TertiaryIntent {};   // E.g. middle mouse button


    // Possible tools
    struct Select {};
    struct Scrub {};
    struct Translate {};
    struct Rotate {};
    struct Scale {};


    struct Info {
        const char* name;
        float color[4];
        Type type;
        EventType eventType;
        entt::entity target;
    };


    struct Data {
        int time;
        int startTime;
        int endTime;

        std::map<int, InputPosition2D> positions;
    };
}