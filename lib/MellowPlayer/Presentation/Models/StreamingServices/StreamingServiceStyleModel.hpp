#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceStyle.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServices)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServiceStyleModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString theme READ getTheme NOTIFY themeChanged)
    Q_PROPERTY(QString accent READ getAccent NOTIFY accentChanged)
    Q_PROPERTY(QString background READ getBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QString foreground READ getForeground NOTIFY foregroundChanged)
    Q_PROPERTY(QString primary READ getPrimary NOTIFY primaryChanged)
    Q_PROPERTY(QString primaryForeground READ getPrimaryForeground NOTIFY primaryForegroundChanged)
    Q_PROPERTY(QString secondary READ getSecondary NOTIFY secondaryChanged)
    Q_PROPERTY(QString secondaryForeground READ getSecondaryForeground NOTIFY secondaryForegroundChanged)
    Q_PROPERTY(bool usePluginStyle READ getUsePluginStyle WRITE setUsePluginStyle NOTIFY usePluginStyleChanged)
public:
    StreamingServiceStyleModel(Application::StreamingServices& streamingServices, Application::Settings& settings);

    QString getTheme() const;
    QString getAccent() const;
    QString getBackground() const;
    QString getForeground() const;
    QString getPrimary() const;
    QString getPrimaryForeground() const;
    QString getSecondary() const;
    QString getSecondaryForeground() const;
    bool getUsePluginStyle() const;
    void setUsePluginStyle(bool value);

    Q_INVOKABLE double getColorScaleFactor(const QString& color) const;
    Q_INVOKABLE bool isDark(const QString& color) const;

    Application::StreamingServiceStyle getDefaultStyle();

signals:
    void themeChanged();
    void accentChanged();
    void backgroundChanged();
    void foregroundChanged();
    void primaryChanged();
    void primaryForegroundChanged();
    void secondaryChanged();
    void secondaryForegroundChanged();
    void usePluginStyleChanged();

private slots:
    void updateStyle();
    void onPluginChanged(Application::StreamingService* streamingService);

private:
    void setAccent(const QString& value);
    void setBackground(const QString& value);
    void setForeground(const QString& value);
    void setPrimary(const QString& value);
    void setPrimaryForeground(const QString& value);
    void setSecondary(const QString& value);
    void setSecondaryForeground(const QString& value);
    void fromStyle(const Application::StreamingServiceStyle& newStyle);

    bool usePluginStyle;
    Application::StreamingServices& streamingServices;
    Application::Setting& accentColorSetting;
    Application::Setting& adaptiveThemeSetting;
    Application::Setting& backgroundSetting;
    Application::Setting& foregroundSetting;
    Application::Setting& primaryBackgroundSetting;
    Application::Setting& primaryForegroundSetting;
    Application::Setting& secondaryBackgroundSetting;
    Application::Setting& secondaryForegroundSetting;
    Application::StreamingServiceStyle style;
};

END_MELLOWPLAYER_NAMESPACE

