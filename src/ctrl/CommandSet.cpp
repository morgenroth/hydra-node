/*
 * CommandSet.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/CommandSet.h"

namespace ctrl {

	CommandSet::CommandSet(CommandSet *parent, const std::string &codeword)
	 : _parent(parent), _codeword(codeword)
	{
	}

	CommandSet::~CommandSet()
	{
		// delete all childs
		for (cmd_set::iterator it = _commands.begin(); it != _commands.end(); it++) {
			delete *it;
		}
	}

	bool CommandSet::match(const std::string &value) const
	{
		return (value.find(_codeword) == 0);
	}

	CommandSet* CommandSet::enter(const std::string &value)
	{
		for (cmd_set::iterator it = _commands.begin(); it != _commands.end(); it++) {
			CommandSet *entry = (*it);
			if (entry->match(value)) {
				return entry;
			}
		}

		return 0;
	}

	CommandSet* CommandSet::leave()
	{
		return _parent;
	};

	/**
	 * Execute this command with the given parameters.
	 * The stream is used to read more data necessary for this command
	 * and to return the answer.
	 */
	void CommandSet::execute(const std::string &parameters, std::iostream &stream) const
	{
		result(stream, 301, "NOT IMPLEMENTED");
	}

	bool CommandSet::isCommand() const
	{
		return false;
	}

	const std::string& CommandSet::getCode() const
	{
		return _codeword;
	}

	void CommandSet::add(CommandSet *cset)
	{
		_commands.insert(cset);
	}

	void CommandSet::result_fail(std::iostream &stream)
	{
		result(stream, 300, "FAIL");
	}

	void CommandSet::result_ok(std::iostream &stream)
	{
		result(stream, 200, "OK");
	}

	void CommandSet::result(std::iostream &stream, int code, const std::string &msg)
	{
		stream << code << " " << msg << std::endl;
	}
}
