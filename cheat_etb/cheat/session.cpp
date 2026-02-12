#include "session.h"

#include "gvalue.h"
#include "_sdk.h"

void session::create_session(const int& public_player, const int& private_player, const bool& is_private)
{
	SDK::TArray<SDK::FSessionPropertyKeyPair> extra;
	SDK::UCreateSessionCallbackProxyAdvanced::CreateAdvancedSession(
		gvalue::world,
		extra,
		gvalue::controller,
		public_player,
		private_player,
		false,
		true,
		false,
		true,
		true,
		true,
		false,
		false,
		false,
		true,
		true,
		true,
		true
	);

}

void session::open_lobby()
{
	SDK::UGameplayStatics::OpenLevel(
		gvalue::world,
		SDK::UKismetStringLibrary::Conv_StringToName(L"Lobby"),
		true,
		L"listen"
	);
}
