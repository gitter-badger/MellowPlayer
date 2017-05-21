#include <catch.hpp>
#include <MellowPlayer/Presentation/Widgets/SystemTrayIcon.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <MellowPlayer/UseCases/Settings/ApplicationSettings.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("SystemTrayIconTests") {
    auto playerMock = PlayerMock::get();
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto appSettingsMock = SettingsProviderMock::get();
    SettingsSchemaLoader loader;
    ApplicationSettings applicationSettings(loader, appSettingsMock.get());
    SystemTrayIcon systemTrayIcon(playerMock.get(), mainWindowMock.get(), qtAppMock.get(), applicationSettings);

    SECTION("show window onActivated") {
        systemTrayIcon.onActivated(QSystemTrayIcon::Context);
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("togglePlayPause call player") {
        systemTrayIcon.togglePlayPause();
        Verify(Method(playerMock, togglePlayPause)).Exactly(1);
    }

    SECTION("next call player") {
        systemTrayIcon.next();
        Verify(Method(playerMock, next)).Exactly(1);
    }

    SECTION("previous call player") {
        systemTrayIcon.previous();
        Verify(Method(playerMock, previous)).Exactly(1);
    }

    SECTION("restoreWindow show window") {
        systemTrayIcon.restoreWindow();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit quits the application") {
        systemTrayIcon.quit();
        Verify(Method(qtAppMock, quit)).Exactly(1);
    }

    SECTION("show icon") {
        systemTrayIcon.show();
    }
    SECTION("hide icon") {
        systemTrayIcon.hide();
    }
    SECTION("show message") {
        systemTrayIcon.showMessage("Title", "Message");
    }
}
