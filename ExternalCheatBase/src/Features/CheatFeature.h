#ifndef CHEATFEATURE_H
#define CHEATFEATURE_H

class CheatFeature {
public:
    virtual ~CheatFeature() = default;

    virtual void execute() = 0;

    virtual void toggle() { enabled = !enabled; }
    void setEnabled(bool state) { enabled = state; }
    bool isEnabled() const { return enabled; }

protected:
    bool enabled = false;
};

#endif