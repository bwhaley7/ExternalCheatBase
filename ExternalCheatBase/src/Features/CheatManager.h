#ifndef CHEATMANAGER_H
#define CHEATMANAGER_H

#include "CheatFeature.h"
#include <vector>
#include <memory>

class CheatManager {
public:
    void addFeature(std::unique_ptr<CheatFeature> feature) {
        features.emplace_back(std::move(feature));
    }

    void executeAll() {
        for (auto& feature : features) {
            feature->execute();
        }
    }

    void executeEnabled() {
        for (auto& feature : features) {
            if(feature->isEnabled())
                feature->execute();
        }
    }

    void toggleFeature(size_t index) {
        if (index < features.size()) {
            features[index]->toggle();
        }
    }

    void setFeatureState(size_t index, bool state)
    {
        if (index < features.size())
            features[index]->setEnabled(state);
    }

private:
    std::vector<std::unique_ptr<CheatFeature>> features;
};

#endif

inline CheatManager cheatManager;