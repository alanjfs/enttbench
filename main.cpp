#include <map>

#include "entt/entity/registry.hpp"
#include "Components.inl"

entt::registry registry{};


static void init() {
    std::vector<entt::entity> group1{ 51 };
    std::vector<entt::entity> group2{ 27 };
    std::vector<entt::entity> group3{ 68 };
    std::vector<entt::entity> group4{ 44 };

    registry.create<Name>(group1.begin(), group1.end());
    registry.create<Position>(group2.begin(), group2.end());

    for (auto entity : group1) {
        registry.assign<Orientation>(entity);
        registry.assign<Size>(entity);
        registry.assign<InitialSize>(entity);
        registry.assign<Index>(entity);
    }

    for (auto entity : group2) {
        registry.assign<Color>(entity);
        registry.assign<Size>(entity);
        registry.assign<InputPosition2D>(entity);
        registry.assign<Input::Device>(entity);
    }

    for (auto entity : group3) {
        registry.assign<Input::GamepadDevice>(entity);
        registry.assign<Intent::Move>(entity);
        registry.assign<Tool::Type>(entity);
        registry.assign<Tool::Data>(entity);
    }

    for (auto entity : group4) {
        registry.assign<Tool::Data>(entity);
        registry.assign<Tool::Select>(entity);
        registry.assign<Tool::PrimaryIntent>(entity);
        registry.assign<Tool::CanRecord>(entity);
    }

    registry.assign<Selected>(group1.front());
    registry.assign<Hovered>(group2.front());
}


static void test_view() {
    registry.view<Orientation>().each([](auto entity, const auto& orientation) { /* */ });
    registry.view<Size, Orientation>().each([](auto entity, const auto& size, const auto& orientation) { /* */ });

    auto setup = []() {};
    auto begin = [](const auto& info, const auto& data) {};
    auto preview = [](const auto& info, const auto& data) {};
    auto update = [](const auto& info, const auto& data, auto& intent) {};
    auto finish = [](const auto& info, const auto& data) {};

    struct Options {
        float x, y, z;
    } options;

    entt::entity current_item;

    struct This {
        bool self;
    } _this;

    registry.view<Input::MouseDevice, Input::AssignedTool>().each([&](auto& device, auto& tool) { });
    registry.view<Intent::Move, Position>().each([](const auto& intent, auto& position) { });
    registry.view<Intent::Rotate, Orientation>().each([](const auto& intent, auto& orientation) { });
    registry.view<Intent::Scale, Size>().each([](const auto& intent, auto& size) { });
    registry.view<Intent::SortTracks>().less([]() { });
    registry.view<Input::LastUsedDevice>().less([&](auto entity) { });
    registry.view<Position, InitialPosition>().each([&](auto& position, const auto& initial) { });
    registry.view<Orientation>().each([&](auto& orientation) { });
    registry.view<Size, InitialSize>().each([&](auto& size, const auto& initial) { });
    registry.view<Input::MouseDevice>().each([](auto& device) { });
    registry.view<Tool::Info>().each([](auto entity, const auto& meta) { });
    registry.view<Input::MouseDevice>().each([](auto& device) { });
    registry.view<Input::Device>().each([&options, &current_item](auto entity, const auto& device) { });
        registry.view<Name, Position, Orientation, Color, Size>().each([&](auto entity,
                                                                           const auto& name,
                                                                           const auto& position,
                                                                           const auto& orientation,
                                                                           const auto& color,
                                                                           const auto& size) {});
    registry.view<Tool::Data, Tool::Info>().each([&](auto entity, const auto& data, const auto& meta) { });
    registry.view<Input::Device>().each([_this](auto entity, const auto& device) { });
    registry.view<Hovered>();
    registry.view<Hovered>();
    registry.view<Tool::Translate, Tool::SetupIntent>().less(setup);
    registry.view<Tool::Translate, Tool::PrimaryIntent, Tool::BeginIntent, Tool::Info, Tool::Data>().less(begin);
    registry.view<Tool::Translate, Tool::PrimaryIntent, Tool::PreviewIntent, Tool::Info, Tool::Data>().less(preview);
    registry.view<Tool::Translate, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::UpdateIntent>().less(update);
    registry.view<Tool::Rotate, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::BeginIntent>().less(begin);
    registry.view<Tool::Rotate, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::PreviewIntent>().less(preview);
    registry.view<Tool::Rotate, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::UpdateIntent>().less(update);
    registry.view<Tool::Rotate, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::FinishIntent>().less(finish);
    registry.view<Tool::Scale, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::BeginIntent>().less(begin);
    registry.view<Tool::Scale, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::PreviewIntent>().less(preview);
    registry.view<Tool::Scale, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::UpdateIntent>().less(update);
    registry.view<Tool::Scale, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::FinishIntent>().less(finish);
    registry.view<Tool::RecordIntent, Tool::CanRecord, Tool::BeginIntent, Tool::Info, Tool::Data>().less(begin);
    registry.view<Tool::RecordIntent, Tool::CanRecord, Tool::UpdateIntent, Tool::Data>().less(update);
    registry.view<Tool::RecordIntent, Tool::CanRecord, Tool::Info, Tool::Data, Tool::FinishIntent>().less(finish);
    registry.view<Tool::Select, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::BeginIntent>().less(begin);
    registry.view<Tool::Scrub, Tool::PrimaryIntent, Tool::Info, Tool::Data, Tool::UpdateIntent>().less(update);
}


static void test_for() {
    for (auto entity : registry.view<Orientation>()) { /* */ }
    for (auto entity : registry.view<Size, Orientation>()) { /* */ }
    for (auto entity : registry.view<Size, Orientation, Selected>()) { /* */ }
}


int main() {
    init();
    test_view();
    test_for();
    return 0;
}