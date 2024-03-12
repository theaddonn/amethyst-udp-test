#include "dllmain.h"

#include <future>
#include <winrt/windows.networking.sockets.h>
#include <winrt/windows.storage.streams.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.ui.notifications.h>
#include <winrt/windows.data.xml.dom.h>
#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.ui.core.h>
#include <winrt/windows.ui.popups.h>

using namespace winrt;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;

winrt::Windows::Networking::Sockets::DatagramSocket local_socket;

winrt::Windows::Foundation::IAsyncAction send_packet(std::string data)
{
    try
    {
        // If the socket is not already connected, connect to the local server on port 12345
        if (!local_socket.Information().LocalAddress())
        {
            co_await local_socket.ConnectAsync(winrt::Windows::Networking::HostName(L"127.0.0.1"), L"12345");
        }

        // Create a message to send
        std::wstring message(data.begin(), data.end());
        winrt::Windows::Storage::Streams::DataWriter writer;
        writer.WriteString(message);

        // Send the message
        co_await local_socket.OutputStream().WriteAsync(writer.DetachBuffer());

        writer.Close();

        std::wcout << L"Message sent successfully!" << std::endl;
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wcerr << L"Error: " << ex.message().c_str() << std::endl;
    }
}

// Ran when the mod is loaded into the game by AmethystRuntime
ModFunction void Initialize(HookManager* hookManager, Amethyst::EventManager* eventManager, InputManager* inputManager) 
{
    // Logging from <Amethyst/Log.h>
    Log::Info("Hello, Amethyst World!");
    send_packet("Mod init");

    // Add a listener to a built-in amethyst event
    eventManager->onStartJoinGame.AddListener(OnStartJoinGame);
    eventManager->onRequestLeaveGame.AddListener(onRequestLeaveGame);
}

// Subscribed to amethysts on start join game event in Initialize
void OnStartJoinGame(ClientInstance* client)
{
    Log::Info("The player has joined the game!");
    send_packet("Player joined world!");
}

void onRequestLeaveGame() {
    Log::Info("The player has left the game!");
    send_packet("Player left world!");
}