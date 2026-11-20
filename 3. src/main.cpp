#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <vector>

using namespace geode::prelude;

struct DynamicZone {
    int startFrame;
    int endFrame;
    int jitterFrames;
    float clickGain;
    float musicGain;
};

class $modify(DynamicClickPlayLayer, PlayLayer) {
    struct Fields {
        int m_frameCounter = 0;
        std::vector<int> m_recordedFrames;
        std::vector<DynamicZone> m_zones = {
            {0, 180, 2, 0.95f, 0.72f},
            {181, 600, 1, 1.15f, 0.55f}
        };
    };

    const DynamicZone* getActiveZone(int frame) const {
        for (const auto& zone : m_fields->m_zones) {
            if (frame >= zone.startFrame && frame <= zone.endFrame) {
                return &zone;
            }
        }
        return nullptr;
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }
        m_fields->m_frameCounter = 0;
        m_fields->m_recordedFrames.clear();
        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);
        m_fields->m_frameCounter++;

        // Ejemplo: consultar la zona dinamica activa en este frame
        if (const auto* active = getActiveZone(m_fields->m_frameCounter)) {
            // Aqui podes aplicar la logica de tu zona (jitter, ganancia, etc.)
            (void)active;
        }
    }

    void pushButton(int player, bool isRight) {
        PlayLayer::pushButton(player, isRight);
        m_fields->m_recordedFrames.push_back(m_fields->m_frameCounter);
    }

    void releaseButton(int player, bool isRight) {
        PlayLayer::releaseButton(player, isRight);
    }
};

