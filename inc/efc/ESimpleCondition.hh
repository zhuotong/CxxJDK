/*
 * ESimpleCondition.hh
 *
 *  Created on: 2013-3-18
 *      Author: Administrator
 */

#ifndef ESIMPLE_CONDITION_HH_
#define ESIMPLE_CONDITION_HH_

#include "ECondition.hh"
#include "EDate.hh"
#include "ERuntimeException.hh"
#include "EFileNotFoundException.hh"

namespace efc {

/**
 * A Simple condition.
 */

class ESimpleCondition : public ECondition {
public:
	~ESimpleCondition();

	ESimpleCondition(es_thread_mutex_t *mutex);

	//TODO:
	ESimpleCondition(const ESimpleCondition& that);
	ESimpleCondition& operator= (const ESimpleCondition& that);

	/**
	 * Causes the current thread to wait until it is signalled or
	 * {@linkplain Thread#interrupt interrupted}.
	 *
	 * <p>The lock associated with this {@code Condition} is atomically
	 * released and the current thread becomes disabled for thread scheduling
	 * purposes and lies dormant until <em>one</em> of four things happens:
	 * <ul>
	 * <li>Some other thread invokes the {@link #signal} method for this
	 * {@code Condition} and the current thread happens to be chosen as the
	 * thread to be awakened; or
	 * <li>Some other thread invokes the {@link #signalAll} method for this
	 * {@code Condition}; or
	 * <li>Some other thread {@linkplain Thread#interrupt interrupts} the
	 * current thread, and interruption of thread suspension is supported; or
	 * <li>A &quot;<em>spurious wakeup</em>&quot; occurs.
	 * </ul>
	 *
	 * <p>In all cases, before this method can return the current thread must
	 * re-acquire the lock associated with this condition. When the
	 * thread returns it is <em>guaranteed</em> to hold this lock.
	 *
	 * <p>If the current thread:
	 * <ul>
	 * <li>has its interrupted status set on entry to this method; or
	 * <li>is {@linkplain Thread#interrupt interrupted} while waiting
	 * and interruption of thread suspension is supported,
	 * </ul>
	 * then {@link InterruptedException} is thrown and the current thread's
	 * interrupted status is cleared. It is not specified, in the first
	 * case, whether or not the test for interruption occurs before the lock
	 * is released.
	 *
	 * <p><b>Implementation Considerations</b>
	 *
	 * <p>The current thread is assumed to hold the lock associated with this
	 * {@code Condition} when this method is called.
	 * It is up to the implementation to determine if this is
	 * the case and if not, how to respond. Typically, an exception will be
	 * thrown (such as {@link IllegalMonitorStateException}) and the
	 * implementation must document that fact.
	 *
	 * <p>An implementation can favor responding to an interrupt over normal
	 * method return in response to a signal. In that case the implementation
	 * must ensure that the signal is redirected to another waiting thread, if
	 * there is one.
	 */
	void await();

	/**
	 * Causes the current thread to wait until it is signalled.
	 *
	 * <p>The lock associated with this condition is atomically
	 * released and the current thread becomes disabled for thread scheduling
	 * purposes and lies dormant until <em>one</em> of three things happens:
	 * <ul>
	 * <li>Some other thread invokes the {@link #signal} method for this
	 * {@code Condition} and the current thread happens to be chosen as the
	 * thread to be awakened; or
	 * <li>Some other thread invokes the {@link #signalAll} method for this
	 * {@code Condition}; or
	 * <li>A &quot;<em>spurious wakeup</em>&quot; occurs.
	 * </ul>
	 *
	 * <p>In all cases, before this method can return the current thread must
	 * re-acquire the lock associated with this condition. When the
	 * thread returns it is <em>guaranteed</em> to hold this lock.
	 *
	 * <p>If the current thread's interrupted status is set when it enters
	 * this method, or it is {@linkplain Thread#interrupt interrupted}
	 * while waiting, it will continue to wait until signalled. When it finally
	 * returns from this method its interrupted status will still
	 * be set.
	 *
	 * <p><b>Implementation Considerations</b>
	 *
	 * <p>The current thread is assumed to hold the lock associated with this
	 * {@code Condition} when this method is called.
	 * It is up to the implementation to determine if this is
	 * the case and if not, how to respond. Typically, an exception will be
	 * thrown (such as {@link IllegalMonitorStateException}) and the
	 * implementation must document that fact.
	 */
	void awaitUninterruptibly() {
		throw EFileNotFoundException(__FILE__, __LINE__);
	}

	/**
	 * Causes the current thread to wait until it is signalled or interrupted,
	 * or the specified waiting time elapses.
	 *
	 * <p>The lock associated with this condition is atomically
	 * released and the current thread becomes disabled for thread scheduling
	 * purposes and lies dormant until <em>one</em> of five things happens:
	 * <ul>
	 * <li>Some other thread invokes the {@link #signal} method for this
	 * {@code Condition} and the current thread happens to be chosen as the
	 * thread to be awakened; or
	 * <li>Some other thread invokes the {@link #signalAll} method for this
	 * {@code Condition}; or
	 * <li>Some other thread {@linkplain Thread#interrupt interrupts} the
	 * current thread, and interruption of thread suspension is supported; or
	 * <li>The specified waiting time elapses; or
	 * <li>A &quot;<em>spurious wakeup</em>&quot; occurs.
	 * </ul>
	 *
	 * <p>In all cases, before this method can return the current thread must
	 * re-acquire the lock associated with this condition. When the
	 * thread returns it is <em>guaranteed</em> to hold this lock.
	 *
	 * <p>If the current thread:
	 * <ul>
	 * <li>has its interrupted status set on entry to this method; or
	 * <li>is {@linkplain Thread#interrupt interrupted} while waiting
	 * and interruption of thread suspension is supported,
	 * </ul>
	 * then {@link InterruptedException} is thrown and the current thread's
	 * interrupted status is cleared. It is not specified, in the first
	 * case, whether or not the test for interruption occurs before the lock
	 * is released.
	 *
	 * <p>The method returns an estimate of the number of nanoseconds
	 * remaining to wait given the supplied {@code nanosTimeout}
	 * value upon return, or a value less than or equal to zero if it
	 * timed out. This value can be used to determine whether and how
	 * long to re-wait in cases where the wait returns but an awaited
	 * condition still does not hold. Typical uses of this method take
	 * the following form:
	 *
	 * <pre>
	 * synchronized boolean aMethod(long timeout, TimeUnit unit) {
	 *   long nanosTimeout = unit.toNanos(timeout);
	 *   while (!conditionBeingWaitedFor) {
	 *     if (nanosTimeout &gt; 0)
	 *         nanosTimeout = theCondition.awaitNanos(nanosTimeout);
	 *      else
	 *        return false;
	 *   }
	 *   // ...
	 * }
	 * </pre>
	 *
	 * <p> Design note: This method requires a nanosecond argument so
	 * as to avoid truncation errors in reporting remaining times.
	 * Such precision loss would make it difficult for programmers to
	 * ensure that total waiting times are not systematically shorter
	 * than specified when re-waits occur.
	 *
	 * <p><b>Implementation Considerations</b>
	 *
	 * <p>The current thread is assumed to hold the lock associated with this
	 * {@code Condition} when this method is called.
	 * It is up to the implementation to determine if this is
	 * the case and if not, how to respond. Typically, an exception will be
	 * thrown (such as {@link IllegalMonitorStateException}) and the
	 * implementation must document that fact.
	 *
	 * <p>An implementation can favor responding to an interrupt over normal
	 * method return in response to a signal, or over indicating the elapse
	 * of the specified waiting time. In either case the implementation
	 * must ensure that the signal is redirected to another waiting thread, if
	 * there is one.
	 *
	 * @param nanosTimeout the maximum time to wait, in nanoseconds
	 * @return an estimate of the {@code nanosTimeout} value minus
	 *         the time spent waiting upon return from this method.
	 *         A positive value may be used as the argument to a
	 *         subsequent call to this method to finish waiting out
	 *         the desired time.  A value less than or equal to zero
	 *         indicates that no time remains.
	 * @throws InterruptedException if the current thread is interrupted
	 *         (and interruption of thread suspension is supported)
	 */
	llong awaitNanos(llong nanosTimeout);

	/**
	 * Causes the current thread to wait until it is signalled or interrupted,
	 * or the specified waiting time elapses. This method is behaviorally
	 * equivalent to:<br>
	 * <pre>
	 *   awaitNanos(unit.toNanos(time)) &gt; 0
	 * </pre>
	 * @param time the maximum time to wait
	 * @param unit the time unit of the {@code time} argument
	 * @return {@code false} if the waiting time detectably elapsed
	 *         before return from the method, else {@code true}
	 * @throws InterruptedException if the current thread is interrupted
	 *         (and interruption of thread suspension is supported)
	 */
	boolean await(llong time, ETimeUnit* unit) THROWS(EInterruptedException);

	/**
	 * Causes the current thread to wait until it is signalled or interrupted,
	 * or the specified deadline elapses.
	 *
	 * <p>The lock associated with this condition is atomically
	 * released and the current thread becomes disabled for thread scheduling
	 * purposes and lies dormant until <em>one</em> of five things happens:
	 * <ul>
	 * <li>Some other thread invokes the {@link #signal} method for this
	 * {@code Condition} and the current thread happens to be chosen as the
	 * thread to be awakened; or
	 * <li>Some other thread invokes the {@link #signalAll} method for this
	 * {@code Condition}; or
	 * <li>Some other thread {@linkplain Thread#interrupt interrupts} the
	 * current thread, and interruption of thread suspension is supported; or
	 * <li>The specified deadline elapses; or
	 * <li>A &quot;<em>spurious wakeup</em>&quot; occurs.
	 * </ul>
	 *
	 * <p>In all cases, before this method can return the current thread must
	 * re-acquire the lock associated with this condition. When the
	 * thread returns it is <em>guaranteed</em> to hold this lock.
	 *
	 *
	 * <p>If the current thread:
	 * <ul>
	 * <li>has its interrupted status set on entry to this method; or
	 * <li>is {@linkplain Thread#interrupt interrupted} while waiting
	 * and interruption of thread suspension is supported,
	 * </ul>
	 * then {@link InterruptedException} is thrown and the current thread's
	 * interrupted status is cleared. It is not specified, in the first
	 * case, whether or not the test for interruption occurs before the lock
	 * is released.
	 *
	 *
	 * <p>The return value indicates whether the deadline has elapsed,
	 * which can be used as follows:
	 * <pre>
	 * synchronized boolean aMethod(Date deadline) {
	 *   boolean stillWaiting = true;
	 *   while (!conditionBeingWaitedFor) {
	 *     if (stillWaiting)
	 *         stillWaiting = theCondition.awaitUntil(deadline);
	 *      else
	 *        return false;
	 *   }
	 *   // ...
	 * }
	 * </pre>
	 *
	 * <p><b>Implementation Considerations</b>
	 *
	 * <p>The current thread is assumed to hold the lock associated with this
	 * {@code Condition} when this method is called.
	 * It is up to the implementation to determine if this is
	 * the case and if not, how to respond. Typically, an exception will be
	 * thrown (such as {@link IllegalMonitorStateException}) and the
	 * implementation must document that fact.
	 *
	 * <p>An implementation can favor responding to an interrupt over normal
	 * method return in response to a signal, or over indicating the passing
	 * of the specified deadline. In either case the implementation
	 * must ensure that the signal is redirected to another waiting thread, if
	 * there is one.
	 *
	 * @param deadline the absolute time to wait until
	 * @return {@code false} if the deadline has elapsed upon return, else
	 *         {@code true}
	 * @throws InterruptedException if the current thread is interrupted
	 *         (and interruption of thread suspension is supported)
	 */
	boolean awaitUntil(EDate* deadline) THROWS(EInterruptedException);

	/**
	 * Wakes up one waiting thread.
	 *
	 * <p>If any threads are waiting on this condition then one
	 * is selected for waking up. That thread must then re-acquire the
	 * lock before returning from {@code await}.
	 */
	void signal();

	/**
	 * Wakes up all waiting threads.
	 *
	 * <p>If any threads are waiting on this condition then they are
	 * all woken up. Each thread must re-acquire the lock before it can
	 * return from {@code await}.
	 */
	void signalAll();

private:
	es_thread_cond_t *m_Cond;
	es_thread_mutex_t *m_Mutex;
};

} /* namespace efc */
#endif /* ESIMPLE_CONDITION_HH_ */
