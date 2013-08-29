/*
 * CommandSet.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef COMMANDSET_H_
#define COMMANDSET_H_

#include <iostream>
#include <set>

namespace ctrl {

	class CommandSet {
	public:
		CommandSet(CommandSet *parent, const std::string &codeword);
		virtual ~CommandSet();

		/**
		 * Returns true, if the given value matches this command.
		 */
		virtual bool match(const std::string &value) const;

		/**
		 * Enter a sub-level of this command set.
		 */
		virtual CommandSet* enter(const std::string &value);

		/**
		 * Leave this command level and returns the parent.
		 */
		virtual CommandSet* leave();

		/**
		 * Execute this command with the given parameters.
		 * The stream is used to read more data necessary for this command
		 * and to return the answer.
		 */
		virtual void execute(const std::string &parameters, std::iostream &stream) const;

		/**
		 * Returns true, if this instance is a command to execute.
		 */
		virtual bool isCommand() const;

		const std::string& getCode() const;

		static void result_fail(std::iostream &stream);
		static void result_ok(std::iostream &stream);
		static void result(std::iostream &stream, int code, const std::string &msg);

	protected:
		void add(CommandSet *cset);

	private:
		typedef std::set<CommandSet*> cmd_set;
		cmd_set _commands;
		CommandSet *_parent;
		const std::string _codeword;
	};

} /* namespace ctrl */
#endif /* COMMANDSET_H_ */
