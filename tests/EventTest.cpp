#include <gtest/gtest.h>
#include <event.h>

using namespace Util;

struct Dummy {
	void called() { calledVal = true; }
	void called1() { calledVal1 = true; }
	bool calledVal = false;
	bool calledVal1 = false;
	int value = 0;
	void setValue(int i) { value = i; }
};

TEST(EventTest, SubInvokeNoArg) {
	Event<> event;
	auto dummy = std::make_shared<Dummy>();
	event.subscribe(std::weak_ptr(dummy), &Dummy::called);
	event.invoke();
	EXPECT_TRUE(dummy->calledVal);
}

TEST(EventTest, SubInvokeArg) {
	Event<int> event;
	auto dummy = std::make_shared<Dummy>();
	event.subscribe(std::weak_ptr(dummy), &Dummy::setValue);
	event.invoke(42);
	EXPECT_EQ(dummy->value, 42);
}

TEST(EventTest, SubInvokeTwoObj) {
	Event<> event;
	auto dummy = std::make_shared<Dummy>();
	auto dummy1 = std::make_shared<Dummy>();
	event.subscribe(std::weak_ptr(dummy), &Dummy::called);
	event.subscribe(std::weak_ptr(dummy1), &Dummy::called);
	event.invoke();
	EXPECT_TRUE(dummy->calledVal);
	EXPECT_TRUE(dummy1->calledVal);
}

TEST(EventTest, SubInvokeTwoFuncs) {
	Event<> event;
	auto dummy = std::make_shared<Dummy>();
	event.subscribe(std::weak_ptr(dummy), &Dummy::called);
	event.subscribe(std::weak_ptr(dummy), &Dummy::called1);
	event.invoke();
	EXPECT_TRUE(dummy->calledVal);
	EXPECT_TRUE(dummy->calledVal1);
}

TEST(EventTest, DeadListener) {
	Event<> event;
	{
		auto dummy = std::make_shared<Dummy>();
		event.subscribe(std::weak_ptr(dummy), &Dummy::called);
	}
	EXPECT_NO_THROW(event.invoke());
}

TEST(EventTest, Unsub) {
	Event<> event;
	auto dummy = std::make_shared<Dummy>();
	event.subscribe(std::weak_ptr(dummy), &Dummy::called);
	event.unsubscribe(std::weak_ptr(dummy), &Dummy::called);
	event.invoke();
	EXPECT_FALSE(dummy->calledVal);
}

TEST(EventTest, UnsubEmpty) {
	Event<> event;
	auto dummy = std::make_shared<Dummy>();
	EXPECT_NO_THROW(event.unsubscribe(std::weak_ptr(dummy), &Dummy::called));
}
