//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#ifndef PLUGINS
#define PLUGINS

#include <QtCore>
#include <QtPlugin>
#include "mellowplayer/song.h"

class QWebView;
class QWidget;


/*!
 * \brief Plugin interface for adding cloud music service integration.
 */
class ICloudMusicService
{
public:
    /*!
     * Evaluates the JavaScript defined by ``scriptSource`` using the main web
     * frame as context and returns the result of the last executed statement.
     *
     * \param scriptSource JavaScript source to evaluate.
     * \return The result of the last JavaScript statement.
     */
    QVariant runJavaScript(const QString& scriptSource);

    //! Returns the cloud music service URL
    virtual QUrl url() = 0;

    //! Starts playing the current song
    virtual void play() = 0;

    //! Pauses the current song
    virtual void pause() = 0;

    //! Stops the current song
    virtual void stop() = 0;

    //! Skips to the next song
    virtual void next() = 0;

    //! Skips to the previous song
    virtual void previous() = 0;

    //! Seeks to the indicated position [µs]
    virtual void seekToPosition(int position) = 0;

    //! Gets the player volume [0.0-1.0]
    virtual float volume() = 0;

    //! Sets the player volume [0.0-1.0]
    virtual void setVolume(float value) = 0;

    //! Gets the current song information
    virtual SongInfo currentSongInfo() = 0;

protected:
    QWebView* webView;  ///< A pointer to the appliction's web view.
};

#define ICloudMusicService_iid "org.MellowPlayer.ICloudMusicService"
Q_DECLARE_INTERFACE(ICloudMusicService, ICloudMusicService_iid)


/*!
 * \brief Plugin inteface for adding a generic extension to the application.
 *
 * An extension plugin can be anything. Since you can access any parts of the
 * application (logic, gui, other plugins), you're free to setup any kind of
 * extension. You can add your own menu or dock widget,...
 *
 * Each plugin may have a settings widgets that will automatically appear in the
 * application settings.
 */
class IExtension
{
public:
    /*!
     * \brief Initalizes the extension.
     *
     * You must implement this method to perform your extension setup.
     *
     * Hint: You can use the Services static class to get access to the most
     * important parts of your application to perform your own specific setup.
     */
    virtual void setup() = 0;

    /*!
     * \brief Destroys the extension.
     *
     * This method is called on application exit.
     *
     * Implement this method if you need to unregister some services or to
     * delete custom allocated objects.
     */
    virtual void teardown() = 0;

    /*!
     * \brief Returns the settings widget associated with the extension.
     *
     * Implement this method if you need to show a settings widget in the
     * application preferences dialog. Return NULL if you don't need to show
     * any settings.
     */
    virtual QWidget* settingsWidget() = 0;
};

#define IExtension_iid "org.MellowPlayer.IExtension"
Q_DECLARE_INTERFACE(IExtension, IExtension_iid)

#endif // PLUGINS

