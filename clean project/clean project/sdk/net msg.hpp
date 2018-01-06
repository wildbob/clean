namespace sdk
{
	struct i_netmessage {
		virtual ~i_netmessage();
	};

	template<typename T>
	class c_netmessagepb : public i_netmessage, public T {};

	class c_msg_move {
	private:
		char __PAD0[0x8];
	public:
		int numBackupCommands;
		int numNewCommands;
	};

	using c_msg_move_t = c_netmessagepb<c_msg_move>;
}