#!/usr/local/bin/oscript

import System.All;

public void Main(int argc, string args) {
	print("AdvancedPrototypeTest.os");
	system("./AdvancedPrototypeTest.os");
	print("BasicPrototypeTest.os");
	system("./BasicPrototypeTest.os");
	print("BasicPrototypeWithInheritanceConstraint.os");
	system("./BasicPrototypeWithInheritanceConstraint.os");
	print("BasicPrototypeWithObjectTest.os");
	system("./BasicPrototypeWithObjectTest.os");
	print("Fail_BasicPrototypeWithInheritanceConstraint.os");
	system("./Fail_BasicPrototypeWithInheritanceConstraint.os");
	print("Fail_PrototypeAssignment.os");
	system("./Fail_PrototypeAssignment.os");
	print("InheritFromPrototypeTest.os");
	system("./InheritFromPrototypeTest.os");
	print("ListTest.os");
	system("./ListTest.os");
	print("PrototypeAsMember.os");
	system("./PrototypeAsMember.os");
	print("PrototypeAsParameter.os");
	system("./PrototypeAsParameter.os");
	print("PrototypeAsPrototypedMember.os");
	system("./PrototypeAsPrototypedMember.os");
	print("PrototypeAsReturnValue.os");
	system("./PrototypeAsReturnValue.os");
}

