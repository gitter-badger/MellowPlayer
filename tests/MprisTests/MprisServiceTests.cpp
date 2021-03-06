#include <QtCore>
#include <catch.hpp>
#ifdef Q_OS_LINUX
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/MprisController.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtDBus/QDBusConnection>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("MprisServiceTests", "[IntegrationTest]")
{
    auto plugionLoaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServicesController streamingServices(plugionLoaderMock.get(), watcherMock.get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();

    MprisController mprisService(player, localAlbumArt, mainWindowMock.get(), qtAppMock.get());
    SECTION("start should succeed the first time")
    {
        if (QDBusConnection::sessionBus().isConnected()) {
            REQUIRE(mprisService.start());

            SECTION("should fail the second time ")
            {
                REQUIRE(!mprisService.start());
            }
        }
    }
}

#endif