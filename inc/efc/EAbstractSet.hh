/*
 * EAbstractSet.hh
 *
 *  Created on: 2013-3-25
 *      Author: Administrator
 */

#ifndef EAbstractSet_HH_
#define EAbstractSet_HH_

#include "ESet.hh"
#include "EAbstractCollection.hh"

namespace efc {

/**
 * This class provides a skeletal implementation of the <tt>Set</tt>
 * interface to minimize the effort required to implement this
 * interface. <p>
 *
 * The process of implementing a set by extending this class is identical
 * to that of implementing a Collection by extending AbstractCollection,
 * except that all of the methods and constructors in subclasses of this
 * class must obey the additional constraints imposed by the <tt>Set</tt>
 * interface (for instance, the add method must not permit addition of
 * multiple instances of an object to a set).<p>
 *
 * Note that this class does not override any of the implementations from
 * the <tt>AbstractCollection</tt> class.  It merely adds implementations
 * for <tt>equals</tt> and <tt>hashCode</tt>.<p>
 *
 * This class is a member of the
 * <a href="{@docRoot}/../technotes/guides/collections/index.html">
 * Java Collections Framework</a>.
 *
 * @param <E> the type of elements maintained by this set
 *
 * @version 1.29, 04/21/06
 * @see Collection
 * @see AbstractCollection
 * @see Set
 * @since 1.2
 */

template<typename E>
abstract class EAbstractSet: virtual public EAbstractCollection<E>,
		virtual public ESet<E> {
protected:
    /**
     * Sole constructor.  (For invocation by subclass constructors, typically
     * implicit.)
     */
    EAbstractSet() {
    }

public:
    virtual ~EAbstractSet(){}

    virtual boolean contains(E o) {
		return EAbstractCollection<E>::contains(o);
	}

    virtual boolean containsAll(ECollection<E> *c) {
		return EAbstractCollection<E>::containsAll(c);
	}

    virtual boolean retainAll(ECollection<E> *c) {
		return EAbstractCollection<E>::retainAll(c);
	}

	virtual boolean isEmpty() {
		return EAbstractCollection<E>::isEmpty();
	}

	virtual boolean add(E e) {
		return EAbstractCollection<E>::add(e);
	}

	virtual boolean remove(E o) {
		return EAbstractCollection<E>::remove(o);
	}

	virtual void clear() {
		EAbstractCollection<E>::clear();
	}

	virtual EIterator<E>* iterator(int index=0) {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

	virtual int size() {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

    // Comparison and hashing

    /**
     * Compares the specified object with this set for equality.  Returns
     * <tt>true</tt> if the given object is also a set, the two sets have
     * the same size, and every member of the given set is contained in
     * this set.  This ensures that the <tt>equals</tt> method works
     * properly across different implementations of the <tt>Set</tt>
     * interface.<p>
     *
     * This implementation first checks if the specified object is this
     * set; if so it returns <tt>true</tt>.  Then, it checks if the
     * specified object is a set whose size is identical to the size of
     * this set; if not, it returns false.  If so, it returns
     * <tt>containsAll((Collection) o)</tt>.
     *
     * @param o object to be compared for equality with this set
     * @return <tt>true</tt> if the specified object is equal to this set
     */
    virtual boolean equals(EObject* o) {
		if (o == this)
	    	return true;

		ECollection<E>* c = dynamic_cast<ECollection<E>*>(o);
		if (!c || c->size() != size())
	    	return false;
        
		return containsAll(c);
    }

    /**
	 * Returns the hash code value for this set.  The hash code of a set is
	 * defined to be the sum of the hash codes of the elements in the set,
	 * where the hash code of a <tt>null</tt> element is defined to be zero.
	 * This ensures that <tt>s1.equals(s2)</tt> implies that
	 * <tt>s1.hashCode()==s2.hashCode()</tt> for any two sets <tt>s1</tt>
	 * and <tt>s2</tt>, as required by the general contract of
	 * {@link Object#hashCode}.
	 *
	 * <p>This implementation iterates over the set, calling the
	 * <tt>hashCode</tt> method on each element in the set, and adding up
	 * the results.
	 *
	 * @return the hash code value for this set
	 * @see Object#equals(Object)
	 * @see Set#equals(Object)
	 */
	virtual int hashCode() {
		int h = 0;
		EIterator<E>* i = iterator();
		while (i->hasNext()) {
			E obj = i->next();
			if (obj != null)
				h += obj->hashCode();
		}
		delete i;
		return h;
	}

    /**
     * Removes from this set all of its elements that are contained in the
     * specified collection (optional operation).  If the specified
     * collection is also a set, this operation effectively modifies this
     * set so that its value is the <i>asymmetric set difference</i> of
     * the two sets.
     *
     * <p>This implementation determines which is the smaller of this set
     * and the specified collection, by invoking the <tt>size</tt>
     * method on each.  If this set has fewer elements, then the
     * implementation iterates over this set, checking each element
     * returned by the iterator in turn to see if it is contained in
     * the specified collection.  If it is so contained, it is removed
     * from this set with the iterator's <tt>remove</tt> method.  If
     * the specified collection has fewer elements, then the
     * implementation iterates over the specified collection, removing
     * from this set each element returned by the iterator, using this
     * set's <tt>remove</tt> method.
     *
     * <p>Note that this implementation will throw an
     * <tt>UnsupportedOperationException</tt> if the iterator returned by the
     * <tt>iterator</tt> method does not implement the <tt>remove</tt> method.
     *
     * @param  c collection containing elements to be removed from this set
     * @return <tt>true</tt> if this set changed as a result of the call
     * @throws UnsupportedOperationException if the <tt>removeAll</tt> operation
     *         is not supported by this set
     * @throws ClassCastException if the class of an element of this set
     *         is incompatible with the specified collection (optional)
     * @throws NullPointerException if this set contains a null element and the
     *         specified collection does not permit null elements (optional),
     *         or if the specified collection is null
     * @see #remove(Object)
     * @see #contains(Object)
     */
    virtual boolean removeAll(ECollection<E> *c) {
        boolean modified = false;
		EIterator<E> *i = null;
		
        if (size() > c->size()) {
            for (i = c->iterator(); i->hasNext(); )
                modified |= remove(i->next());
        } else {
            for (i = iterator(); i->hasNext(); ) {
                if (c->contains(i->next())) {
                    i->remove();
                    modified = true;
                }
            }
        }
        delete i;
        return modified;
    }

};

//=============================================================================

template<>
abstract class EAbstractSet<int>: virtual public EAbstractCollection<int>,
		virtual public ESet<int> {
protected:
    /**
     * Sole constructor.  (For invocation by subclass constructors, typically
     * implicit.)
     */
    EAbstractSet() {
    }

public:
	virtual ~EAbstractSet(){}

	virtual boolean contains(int o) {
		return EAbstractCollection<int>::contains(o);
	}

	virtual boolean containsAll(ECollection<int> *c) {
		return EAbstractCollection<int>::containsAll(c);
	}

	virtual boolean retainAll(ECollection<int> *c) {
		return EAbstractCollection<int>::retainAll(c);
	}

	virtual boolean isEmpty() {
		return EAbstractCollection<int>::isEmpty();
	}

	virtual boolean add(int e) {
		return EAbstractCollection<int>::add(e);
	}

	virtual boolean remove(int o) {
		return EAbstractCollection<int>::remove(o);
	}

	virtual void clear() {
		EAbstractCollection<int>::clear();
	}

	virtual EIterator<int>* iterator(int index=0) {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

	virtual int size() {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

    // Comparison and hashing

    /**
     * Compares the specified object with this set for equality.  Returns
     * <tt>true</tt> if the given object is also a set, the two sets have
     * the same size, and every member of the given set is contained in
     * this set.  This ensures that the <tt>equals</tt> method works
     * properly across different implementations of the <tt>Set</tt>
     * interface.<p>
     *
     * This implementation first checks if the specified object is this
     * set; if so it returns <tt>true</tt>.  Then, it checks if the
     * specified object is a set whose size is identical to the size of
     * this set; if not, it returns false.  If so, it returns
     * <tt>containsAll((Collection) o)</tt>.
     *
     * @param o object to be compared for equality with this set
     * @return <tt>true</tt> if the specified object is equal to this set
     */
    virtual boolean equals(ESet<int>* o) {
    	if (o == this)
	    	return true;

		ECollection<int>* c = static_cast<ECollection<int>*>(o);
		if (!c || c->size() != size())
	    	return false;

		return containsAll(c);
    }

	/**
	 * Returns the hash code value for this set.  The hash code of a set is
	 * defined to be the sum of the hash codes of the elements in the set,
	 * where the hash code of a <tt>null</tt> element is defined to be zero.
	 * This ensures that <tt>s1.equals(s2)</tt> implies that
	 * <tt>s1.hashCode()==s2.hashCode()</tt> for any two sets <tt>s1</tt>
	 * and <tt>s2</tt>, as required by the general contract of
	 * {@link Object#hashCode}.
	 *
	 * <p>This implementation iterates over the set, calling the
	 * <tt>hashCode</tt> method on each element in the set, and adding up
	 * the results.
	 *
	 * @return the hash code value for this set
	 * @see Object#equals(Object)
	 * @see Set#equals(Object)
	 */
	virtual int hashCode() {
		int h = 0;
		EIterator<int>* i = iterator();
		while (i->hasNext()) {
			h += i->next();
		}
		delete i;
		return h;
	}

    /**
     * Removes from this set all of its elements that are contained in the
     * specified collection (optional operation).  If the specified
     * collection is also a set, this operation effectively modifies this
     * set so that its value is the <i>asymmetric set difference</i> of
     * the two sets.
     *
     * <p>This implementation determines which is the smaller of this set
     * and the specified collection, by invoking the <tt>size</tt>
     * method on each.  If this set has fewer elements, then the
     * implementation iterates over this set, checking each element
     * returned by the iterator in turn to see if it is contained in
     * the specified collection.  If it is so contained, it is removed
     * from this set with the iterator's <tt>remove</tt> method.  If
     * the specified collection has fewer elements, then the
     * implementation iterates over the specified collection, removing
     * from this set each element returned by the iterator, using this
     * set's <tt>remove</tt> method.
     *
     * <p>Note that this implementation will throw an
     * <tt>UnsupportedOperationException</tt> if the iterator returned by the
     * <tt>iterator</tt> method does not implement the <tt>remove</tt> method.
     *
     * @param  c collection containing elements to be removed from this set
     * @return <tt>true</tt> if this set changed as a result of the call
     * @throws UnsupportedOperationException if the <tt>removeAll</tt> operation
     *         is not supported by this set
     * @throws ClassCastException if the class of an element of this set
     *         is incompatible with the specified collection (optional)
     * @throws NullPointerException if this set contains a null element and the
     *         specified collection does not permit null elements (optional),
     *         or if the specified collection is null
     * @see #remove(Object)
     * @see #contains(Object)
     */
    virtual boolean removeAll(ECollection<int> *c) {
        boolean modified = false;
		EIterator<int> *i = null;

        if (size() > c->size()) {
            for (i = c->iterator(); i->hasNext(); )
                modified |= remove(i->next());
        } else {
            for (i = iterator(); i->hasNext(); ) {
                if (c->contains(i->next())) {
                    i->remove();
                    modified = true;
                }
            }
        }
        delete i;
        return modified;
    }

};

//=============================================================================

template<>
abstract class EAbstractSet<llong>: virtual public EAbstractCollection<llong>,
		virtual public ESet<llong> {
protected:
    /**
     * Sole constructor.  (For invocation by subclass constructors, typically
     * implicit.)
     */
    EAbstractSet() {
    }

public:
	virtual ~EAbstractSet(){}

	virtual boolean contains(llong o) {
		return EAbstractCollection<llong>::contains(o);
	}

	virtual boolean containsAll(ECollection<llong> *c) {
		return EAbstractCollection<llong>::containsAll(c);
	}

	virtual boolean retainAll(ECollection<llong> *c) {
		return EAbstractCollection<llong>::retainAll(c);
	}

	virtual boolean isEmpty() {
		return EAbstractCollection<llong>::isEmpty();
	}

	virtual boolean add(llong e) {
		return EAbstractCollection<llong>::add(e);
	}

	virtual boolean remove(llong o) {
		return EAbstractCollection<llong>::remove(o);
	}

	virtual void clear() {
		EAbstractCollection<llong>::clear();
	}

	virtual EIterator<llong>* iterator(int index=0) {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

	virtual int size() {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

    // Comparison and hashing

    /**
     * Compares the specified object with this set for equality.  Returns
     * <tt>true</tt> if the given object is also a set, the two sets have
     * the same size, and every member of the given set is contained in
     * this set.  This ensures that the <tt>equals</tt> method works
     * properly across different implementations of the <tt>Set</tt>
     * interface.<p>
     *
     * This implementation first checks if the specified object is this
     * set; if so it returns <tt>true</tt>.  Then, it checks if the
     * specified object is a set whose size is identical to the size of
     * this set; if not, it returns false.  If so, it returns
     * <tt>containsAll((Collection) o)</tt>.
     *
     * @param o object to be compared for equality with this set
     * @return <tt>true</tt> if the specified object is equal to this set
     */
    virtual boolean equals(ESet<llong>* o) {
		if (o == this)
	    	return true;

		ECollection<llong>* c = static_cast<ECollection<llong>*>(o);
		if (!c || c->size() != size())
	    	return false;

		return containsAll(c);
    }

    /**
     * Removes from this set all of its elements that are contained in the
     * specified collection (optional operation).  If the specified
     * collection is also a set, this operation effectively modifies this
     * set so that its value is the <i>asymmetric set difference</i> of
     * the two sets.
     *
     * <p>This implementation determines which is the smaller of this set
     * and the specified collection, by invoking the <tt>size</tt>
     * method on each.  If this set has fewer elements, then the
     * implementation iterates over this set, checking each element
     * returned by the iterator in turn to see if it is contained in
     * the specified collection.  If it is so contained, it is removed
     * from this set with the iterator's <tt>remove</tt> method.  If
     * the specified collection has fewer elements, then the
     * implementation iterates over the specified collection, removing
     * from this set each element returned by the iterator, using this
     * set's <tt>remove</tt> method.
     *
     * <p>Note that this implementation will throw an
     * <tt>UnsupportedOperationException</tt> if the iterator returned by the
     * <tt>iterator</tt> method does not implement the <tt>remove</tt> method.
     *
     * @param  c collection containing elements to be removed from this set
     * @return <tt>true</tt> if this set changed as a result of the call
     * @throws UnsupportedOperationException if the <tt>removeAll</tt> operation
     *         is not supported by this set
     * @throws ClassCastException if the class of an element of this set
     *         is incompatible with the specified collection (optional)
     * @throws NullPointerException if this set contains a null element and the
     *         specified collection does not permit null elements (optional),
     *         or if the specified collection is null
     * @see #remove(Object)
     * @see #contains(Object)
     */
    virtual boolean removeAll(ECollection<llong> *c) {
        boolean modified = false;
		EIterator<llong> *i = null;

        if (size() > c->size()) {
            for (i = c->iterator(); i->hasNext(); )
                modified |= remove(i->next());
        } else {
            for (i = iterator(); i->hasNext(); ) {
                if (c->contains(i->next())) {
                    i->remove();
                    modified = true;
                }
            }
        }
        delete i;
        return modified;
    }
};

} /* namespace efc */
#endif //!EAbstractSet_HH_
