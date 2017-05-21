#pragma once

#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include "SettingModelFactory.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingModel;

class SettingsModel: public QObject {
    Q_OBJECT
public:
    SettingsModel(UseCases::Settings& settings, QObject* parent= nullptr);

    Q_INVOKABLE SettingModel* get(int key);

private:
    UseCases::Settings& settings;
    SettingModelFactory settingModelFactory;
};

END_MELLOWPLAYER_NAMESPACE
