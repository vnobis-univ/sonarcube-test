#include "Response.h"

Response to_response(string s)
{
	if (s == "Created")
		return Response::CREATED;
	else if (s == "Joined")
		return Response::JOINED;
	else if (s == "P1_READY")
		return Response::P1_READY;
	else if (s == "P2_READY")
		return Response::P2_READY;
	else if (s[0] == 'S' && s[1] == 'H' && s[2] == 'O' && s[3] == 'O' && s[4] == 'T')
		return Response::SHOOT;

	return Response::UNEXPECTED_RESP;
}
