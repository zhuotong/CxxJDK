/*
 * EDouble.hh
 *
 *  Created on: 2013-3-25
 *      Author: Administrator
 */

#ifndef EDouble_HH_
#define EDouble_HH_

#include "EObject.hh"
#include "EString.hh"
#include "ENumberFormatException.hh"

namespace efc {

/**
 * The <code>Double</code> class wraps a value of the primitive type
 * <code>double</code> in an object. An object of type
 * <code>Double</code> contains a single field whose type is
 * <code>double</code>.
 * <p>
 * In addition, this class provides several methods for converting a
 * <code>double</code> to a <code>String</code> and a
 * <code>String</code> to a <code>double</code>, as well as other
 * constants and methods useful when dealing with a
 * <code>double</code>.
 *
 * @version 1.100, 04/07/06
 * @since JDK1.0
 */

#define DOUBLE_MAX_VALUE      (1.7976931348623157e+308)
#define DOUBLE_MIN_NORMAL     (2.2250738585072014E-308)
#define DOUBLE_MIN_VALUE      (4.9e-324)
#define DOUBLE_MAX_EXPONENT   1023
#define DOUBLE_MIN_EXPONENT   -102
#define DOUBLE_SIZE           64

class EDouble: virtual public EComparable<EDouble*> {
public:
	/**
	 * A constant holding the largest positive finite value of type
	 * <code>double</code>,
	 * (2-2<sup>-52</sup>)&middot;2<sup>1023</sup>.  It is equal to
	 * the hexadecimal floating-point literal
	 * <code>0x1.fffffffffffffP+1023</code> and also equal to
	 * <code>Double.longBitsToDouble(0x7fefffffffffffffL)</code>.
	 */
	static const double MAX_VALUE; // =  1.7976931348623157e+308;

	/**
	 * A constant holding the smallest positive normal value of type
	 * {@code double}, 2<sup>-1022</sup>.  It is equal to the
	 * hexadecimal floating-point literal {@code 0x1.0p-1022} and also
	 * equal to {@code Double.longBitsToDouble(0x0010000000000000L)}.
	 *
	 * @since 1.6
	 */
	static const double MIN_NORMAL; // = 2.2250738585072014E-308;

	/**
	 * A constant holding the smallest positive nonzero value of type
	 * <code>double</code>, 2<sup>-1074</sup>. It is equal to the
	 * hexadecimal floating-point literal
	 * <code>0x0.0000000000001P-1022</code> and also equal to
	 * <code>Double.longBitsToDouble(0x1L)</code>.
	 */
	static const double MIN_VALUE; // = 4.9e-324;

	/**
	 * Maximum exponent a finite {@code double} variable may have.
	 * It is equal to the value returned by
	 * {@code Math.getExponent(Double.MAX_VALUE)}.
	 *
	 * @since 1.6
	 */
	static const int MAX_EXPONENT; // = 1023;

	/**
	 * Minimum exponent a normalized {@code double} variable may
	 * have.  It is equal to the value returned by
	 * {@code Math.getExponent(Double.MIN_NORMAL)}.
	 *
	 * @since 1.6
	 */
	static const int MIN_EXPONENT; // = -102;

	/**
	 * The number of bits used to represent a <tt>double</tt> value.
	 *
	 * @since 1.5
	 */
	static const int SIZE; // = 64;

	/**
	 * Returns a string representation of the <code>double</code>
	 * argument. All characters mentioned below are ASCII characters.
	 * <ul>
	 * <li>If the argument is NaN, the result is the string
	 *     &quot;<code>NaN</code>&quot;.
	 * <li>Otherwise, the result is a string that represents the sign and
	 * magnitude (absolute value) of the argument. If the sign is negative,
	 * the first character of the result is '<code>-</code>'
	 * (<code>'&#92;u002D'</code>); if the sign is positive, no sign character
	 * appears in the result. As for the magnitude <i>m</i>:
	 * <ul>
	 * <li>If <i>m</i> is infinity, it is represented by the characters
	 * <code>"Infinity"</code>; thus, positive infinity produces the result
	 * <code>"Infinity"</code> and negative infinity produces the result
	 * <code>"-Infinity"</code>.
	 *
	 * <li>If <i>m</i> is zero, it is represented by the characters
	 * <code>"0.0"</code>; thus, negative zero produces the result
	 * <code>"-0.0"</code> and positive zero produces the result
	 * <code>"0.0"</code>.
	 *
	 * <li>If <i>m</i> is greater than or equal to 10<sup>-3</sup> but less
	 * than 10<sup>7</sup>, then it is represented as the integer part of
	 * <i>m</i>, in decimal form with no leading zeroes, followed by
	 * '<code>.</code>' (<code>'&#92;u002E'</code>), followed by one or
	 * more decimal digits representing the fractional part of <i>m</i>.
	 *
	 * <li>If <i>m</i> is less than 10<sup>-3</sup> or greater than or
	 * equal to 10<sup>7</sup>, then it is represented in so-called
	 * "computerized scientific notation." Let <i>n</i> be the unique
	 * integer such that 10<sup><i>n</i></sup> &lt;= <i>m</i> &lt;
	 * 10<sup><i>n</i>+1</sup>; then let <i>a</i> be the
	 * mathematically exact quotient of <i>m</i> and
	 * 10<sup><i>n</i></sup> so that 1 &lt;= <i>a</i> &lt; 10. The
	 * magnitude is then represented as the integer part of <i>a</i>,
	 * as a single decimal digit, followed by '<code>.</code>'
	 * (<code>'&#92;u002E'</code>), followed by decimal digits
	 * representing the fractional part of <i>a</i>, followed by the
	 * letter '<code>E</code>' (<code>'&#92;u0045'</code>), followed
	 * by a representation of <i>n</i> as a decimal integer, as
	 * produced by the method {@link Integer#toString(int)}.
	 * </ul>
	 * </ul>
	 * How many digits must be printed for the fractional part of
	 * <i>m</i> or <i>a</i>? There must be at least one digit to represent
	 * the fractional part, and beyond that as many, but only as many, more
	 * digits as are needed to uniquely distinguish the argument value from
	 * adjacent values of type <code>double</code>. That is, suppose that
	 * <i>x</i> is the exact mathematical value represented by the decimal
	 * representation produced by this method for a finite nonzero argument
	 * <i>d</i>. Then <i>d</i> must be the <code>double</code> value nearest
	 * to <i>x</i>; or if two <code>double</code> values are equally close
	 * to <i>x</i>, then <i>d</i> must be one of them and the least
	 * significant bit of the significand of <i>d</i> must be <code>0</code>.
	 * <p>
	 * To create localized string representations of a floating-point
	 * value, use subclasses of {@link java.text.NumberFormat}.
	 *
	 * @param   d   the <code>double</code> to be converted.
	 * @return a string representation of the argument.
	 */
	static EString toString(double d);

	/**
	 * Returns a <code>Double</code> object holding the
	 * <code>double</code> value represented by the argument string
	 * <code>s</code>.
	 *
	 * <p>If <code>s</code> is <code>null</code>, then a
	 * <code>NullPointerException</code> is thrown.
	 *
	 * <p>Leading and trailing whitespace characters in <code>s</code>
	 * are ignored.  Whitespace is removed as if by the {@link
	 * String#trim} method; that is, both ASCII space and control
	 * characters are removed. The rest of <code>s</code> should
	 * constitute a <i>FloatValue</i> as described by the lexical
	 * syntax rules:
	 *
	 * <blockquote>
	 * <dl>
	 * <dt><i>FloatValue:</i>
	 * <dd><i>Sign<sub>opt</sub></i> <code>NaN</code>
	 * <dd><i>Sign<sub>opt</sub></i> <code>Infinity</code>
	 * <dd><i>Sign<sub>opt</sub> FloatingPointLiteral</i>
	 * <dd><i>Sign<sub>opt</sub> HexFloatingPointLiteral</i>
	 * <dd><i>SignedInteger</i>
	 * </dl>
	 *
	 * <p>
	 *
	 * <dl>
	 * <dt><i>HexFloatingPointLiteral</i>:
	 * <dd> <i>HexSignificand BinaryExponent FloatTypeSuffix<sub>opt</sub></i>
	 * </dl>
	 *
	 * <p>
	 *
	 * <dl>
	 * <dt><i>HexSignificand:</i>
	 * <dd><i>HexNumeral</i>
	 * <dd><i>HexNumeral</i> <code>.</code>
	 * <dd><code>0x</code> <i>HexDigits<sub>opt</sub>
	 *     </i><code>.</code><i> HexDigits</i>
	 * <dd><code>0X</code><i> HexDigits<sub>opt</sub>
	 *     </i><code>.</code> <i>HexDigits</i>
	 * </dl>
	 *
	 * <p>
	 *
	 * <dl>
	 * <dt><i>BinaryExponent:</i>
	 * <dd><i>BinaryExponentIndicator SignedInteger</i>
	 * </dl>
	 *
	 * <p>
	 *
	 * <dl>
	 * <dt><i>BinaryExponentIndicator:</i>
	 * <dd><code>p</code>
	 * <dd><code>P</code>
	 * </dl>
	 *
	 * </blockquote>
	 *
	 * where <i>Sign</i>, <i>FloatingPointLiteral</i>,
	 * <i>HexNumeral</i>, <i>HexDigits</i>, <i>SignedInteger</i> and
	 * <i>FloatTypeSuffix</i> are as defined in the lexical structure
	 * sections of the of the <a
	 * href="http://java.sun.com/docs/books/jls/html/">Java Language
	 * Specification</a>. If <code>s</code> does not have the form of
	 * a <i>FloatValue</i>, then a <code>NumberFormatException</code>
	 * is thrown. Otherwise, <code>s</code> is regarded as
	 * representing an exact decimal value in the usual
	 * &quot;computerized scientific notation&quot; or as an exact
	 * hexadecimal value; this exact numerical value is then
	 * conceptually converted to an &quot;infinitely precise&quot;
	 * binary value that is then rounded to type <code>double</code>
	 * by the usual round-to-nearest rule of IEEE 754 floating-point
	 * arithmetic, which includes preserving the sign of a zero
	 * value. Finally, a <code>Double</code> object representing this
	 * <code>double</code> value is returned.
	 *
	 * <p> To interpret localized string representations of a
	 * floating-point value, use subclasses of {@link
	 * java.text.NumberFormat}.
	 *
	 * <p>Note that trailing format specifiers, specifiers that
	 * determine the type of a floating-point literal
	 * (<code>1.0f</code> is a <code>float</code> value;
	 * <code>1.0d</code> is a <code>double</code> value), do
	 * <em>not</em> influence the results of this method.  In other
	 * words, the numerical value of the input string is converted
	 * directly to the target floating-point type.  The two-step
	 * sequence of conversions, string to <code>float</code> followed
	 * by <code>float</code> to <code>double</code>, is <em>not</em>
	 * equivalent to converting a string directly to
	 * <code>double</code>. For example, the <code>float</code>
	 * literal <code>0.1f</code> is equal to the <code>double</code>
	 * value <code>0.10000000149011612</code>; the <code>float</code>
	 * literal <code>0.1f</code> represents a different numerical
	 * value than the <code>double</code> literal
	 * <code>0.1</code>. (The numerical value 0.1 cannot be exactly
	 * represented in a binary floating-point number.)
	 *
	 * <p>To avoid calling this method on an invalid string and having
	 * a <code>NumberFormatException</code> be thrown, the regular
	 * expression below can be used to screen the input string:
	 *
	 * <code>
	 * <pre>
	 *	final String Digits	= "(\\p{Digit}+)";
	 *  final String HexDigits  = "(\\p{XDigit}+)";
	 *	// an exponent is 'e' or 'E' followed by an optionally
	 *	// signed decimal integer.
	 *	final String Exp	= "[eE][+-]?"+Digits;
	 *	final String fpRegex	=
	 *	    ("[\\x00-\\x20]*"+	// Optional leading &quot;whitespace&quot;
	 *	     "[+-]?(" +	// Optional sign character
	 *	     "NaN|" +		// "NaN" string
	 *	     "Infinity|" +	// "Infinity" string
	 *
	 *	     // A decimal floating-point string representing a finite positive
	 *	     // number without a leading sign has at most five basic pieces:
	 *	     // Digits . Digits ExponentPart FloatTypeSuffix
	 *	     //
	 *	     // Since this method allows integer-only strings as input
	 *	     // in addition to strings of floating-point literals, the
	 *	     // two sub-patterns below are simplifications of the grammar
	 *	     // productions from the Java Language Specification, 2nd
	 *	     // edition, section 3.10.2.
	 *
	 *	     // Digits ._opt Digits_opt ExponentPart_opt FloatTypeSuffix_opt
	 *	     "((("+Digits+"(\\.)?("+Digits+"?)("+Exp+")?)|"+
	 *
	 *	     // . Digits ExponentPart_opt FloatTypeSuffix_opt
	 *	     "(\\.("+Digits+")("+Exp+")?)|"+
	 *
	 *       // Hexadecimal strings
	 *       "((" +
	 *        // 0[xX] HexDigits ._opt BinaryExponent FloatTypeSuffix_opt
	 *        "(0[xX]" + HexDigits + "(\\.)?)|" +
	 *
	 *        // 0[xX] HexDigits_opt . HexDigits BinaryExponent FloatTypeSuffix_opt
	 *        "(0[xX]" + HexDigits + "?(\\.)" + HexDigits + ")" +
	 *
	 *        ")[pP][+-]?" + Digits + "))" +
	 *	     "[fFdD]?))" +
	 *	     "[\\x00-\\x20]*");// Optional trailing &quot;whitespace&quot;
	 *
	 *  if (Pattern.matches(fpRegex, myString))
	 *	    Double.valueOf(myString); // Will not throw NumberFormatException
	 *	else {
	 *	    // Perform suitable alternative action
	 *	}
	 * </pre>
	 * </code>
	 *
	 * @param      s   the string to be parsed.
	 * @return     a <code>Double</code> object holding the value
	 *             represented by the <code>String</code> argument.
	 * @exception  NumberFormatException  if the string does not contain a
	 *               parsable number.
	 */
	static EDouble valueOf(const char* s) THROWS(ENumberFormatException);

	/**
	 * Returns a <tt>Double</tt> instance representing the specified
	 * <tt>double</tt> value.
	 * If a new <tt>Double</tt> instance is not required, this method
	 * should generally be used in preference to the constructor
	 * {@link #Double(double)}, as this method is likely to yield
	 * significantly better space and time performance by caching
	 * frequently requested values.
	 *
	 * @param  d a double value.
	 * @return a <tt>Double</tt> instance representing <tt>d</tt>.
	 * @since  1.5
	 */
	static EDouble valueOf(double d);

	/**
	 * Returns a new <code>double</code> initialized to the value
	 * represented by the specified <code>String</code>, as performed
	 * by the <code>valueOf</code> method of class
	 * <code>Double</code>.
	 *
	 * @param      s   the string to be parsed.
	 * @return the <code>double</code> value represented by the string
	 *         argument.
	 * @exception NumberFormatException if the string does not contain
	 *            a parsable <code>double</code>.
	 * @see        java.lang.Double#valueOf(String)
	 * @since 1.2
	 */
	static double parseDouble(const char* s) THROWS(ENumberFormatException);

	/**
	 * Returns a representation of the specified floating-point value
	 * according to the IEEE 754 floating-point "double
	 * format" bit layout.
	 * <p>
	 * Bit 63 (the bit that is selected by the mask
	 * <code>0x8000000000000000L</code>) represents the sign of the
	 * floating-point number. Bits
	 * 62-52 (the bits that are selected by the mask
	 * <code>0x7ff0000000000000L</code>) represent the exponent. Bits 51-0
	 * (the bits that are selected by the mask
	 * <code>0x000fffffffffffffL</code>) represent the significand
	 * (sometimes called the mantissa) of the floating-point number.
	 * <p>
	 * If the argument is positive infinity, the result is
	 * <code>0x7ff0000000000000L</code>.
	 * <p>
	 * If the argument is negative infinity, the result is
	 * <code>0xfff0000000000000L</code>.
	 * <p>
	 * If the argument is NaN, the result is
	 * <code>0x7ff8000000000000L</code>.
	 * <p>
	 * In all cases, the result is a <code>long</code> integer that, when
	 * given to the {@link #longBitsToDouble(long)} method, will produce a
	 * floating-point value the same as the argument to
	 * <code>doubleToLongBits</code> (except all NaN values are
	 * collapsed to a single &quot;canonical&quot; NaN value).
	 *
	 * @param   value   a <code>double</code> precision floating-point number.
	 * @return the bits that represent the floating-point number.
	 */
	static llong doubleToLLongBits(double value);

	/**
	 * Returns the <code>double</code> value corresponding to a given
	 * bit representation.
	 * The argument is considered to be a representation of a
	 * floating-point value according to the IEEE 754 floating-point
	 * "double format" bit layout.
	 * <p>
	 * If the argument is <code>0x7ff0000000000000L</code>, the result
	 * is positive infinity.
	 * <p>
	 * If the argument is <code>0xfff0000000000000L</code>, the result
	 * is negative infinity.
	 * <p>
	 * If the argument is any value in the range
	 * <code>0x7ff0000000000001L</code> through
	 * <code>0x7fffffffffffffffL</code> or in the range
	 * <code>0xfff0000000000001L</code> through
	 * <code>0xffffffffffffffffL</code>, the result is a NaN.  No IEEE
	 * 754 floating-point operation provided by Java can distinguish
	 * between two NaN values of the same type with different bit
	 * patterns.  Distinct values of NaN are only distinguishable by
	 * use of the <code>Double.doubleToRawLongBits</code> method.
	 * <p>
	 * In all other cases, let <i>s</i>, <i>e</i>, and <i>m</i> be three
	 * values that can be computed from the argument:
	 * <blockquote><pre>
	 * int s = ((bits &gt;&gt; 63) == 0) ? 1 : -1;
	 * int e = (int)((bits &gt;&gt; 52) & 0x7ffL);
	 * long m = (e == 0) ?
	 *                 (bits & 0xfffffffffffffL) &lt;&lt; 1 :
	 *                 (bits & 0xfffffffffffffL) | 0x10000000000000L;
	 * </pre></blockquote>
	 * Then the floating-point result equals the value of the mathematical
	 * expression <i>s</i>&middot;<i>m</i>&middot;2<sup><i>e</i>-1075</sup>.
	 *<p>
	 * Note that this method may not be able to return a
	 * <code>double</code> NaN with exactly same bit pattern as the
	 * <code>long</code> argument.  IEEE 754 distinguishes between two
	 * kinds of NaNs, quiet NaNs and <i>signaling NaNs</i>.  The
	 * differences between the two kinds of NaN are generally not
	 * visible in Java.  Arithmetic operations on signaling NaNs turn
	 * them into quiet NaNs with a different, but often similar, bit
	 * pattern.  However, on some processors merely copying a
	 * signaling NaN also performs that conversion.  In particular,
	 * copying a signaling NaN to return it to the calling method
	 * may perform this conversion.  So <code>longBitsToDouble</code>
	 * may not be able to return a <code>double</code> with a
	 * signaling NaN bit pattern.  Consequently, for some
	 * <code>long</code> values,
	 * <code>doubleToRawLongBits(longBitsToDouble(start))</code> may
	 * <i>not</i> equal <code>start</code>.  Moreover, which
	 * particular bit patterns represent signaling NaNs is platform
	 * dependent; although all NaN bit patterns, quiet or signaling,
	 * must be in the NaN range identified above.
	 *
	 * @param   bits   any <code>long</code> integer.
	 * @return  the <code>double</code> floating-point value with the same
	 *          bit pattern.
	 */
	static double llongBitsToDouble(llong bits);

	/**
	 * Compares the two specified <code>double</code> values. The sign
	 * of the integer value returned is the same as that of the
	 * integer that would be returned by the call:
	 * <pre>
	 *    new Double(d1).compareTo(new Double(d2))
	 * </pre>
	 *
	 * @param   d1        the first <code>double</code> to compare
	 * @param   d2        the second <code>double</code> to compare
	 * @return  the value <code>0</code> if <code>d1</code> is
	 *		numerically equal to <code>d2</code>; a value less than
	 *          <code>0</code> if <code>d1</code> is numerically less than
	 *		<code>d2</code>; and a value greater than <code>0</code>
	 *		if <code>d1</code> is numerically greater than
	 *		<code>d2</code>.
	 * @since 1.4
	 */
	static int compare(double d1, double d2);

public:
	virtual ~EDouble() {
	}

	/**
	 * Constructs a newly allocated <code>Double</code> object that
	 * represents the primitive <code>double</code> argument.
	 *
	 * @param   value   the value to be represented by the <code>Double</code>.
	 */
	EDouble(double value);

	/**
	 * Constructs a newly allocated <code>Float</code> object that
	 * represents the floating-point value of type <code>float</code>
	 * represented by the string. The string is converted to a
	 * <code>float</code> value as if by the <code>valueOf</code> method.
	 *
	 * @param      s   a string to be converted to a <code>Float</code>.
	 * @exception  NumberFormatException  if the string does not contain a
	 *               parsable number.
	 * @see        java.lang.Float#valueOf(java.lang.String)
	 */
	EDouble(const char* s) THROWS(ENumberFormatException);

	/**
	 * Returns a string representation of this <code>Float</code> object.
	 * The primitive <code>float</code> value represented by this object
	 * is converted to a <code>String</code> exactly as if by the method
	 * <code>toString</code> of one argument.
	 *
	 * @return  a <code>String</code> representation of this object.
	 * @see java.lang.Float#toString(float)
	 */
	virtual EStringBase toString();

	byte byteValue();
	short shortValue();
	int intValue();
	long longValue();
	float floatValue();
	double doubleValue();

	/**
	 * Returns a hash code for this <code>Float</code> object. The
	 * result is the integer bit representation, exactly as produced
	 * by the method {@link #floatToIntBits(float)}, of the primitive
	 * <code>float</code> value represented by this <code>Float</code>
	 * object.
	 *
	 * @return a hash code value for this object.
	 */
	virtual int hashCode();

	/**
	 * Compares this object against the specified object.  The result
	 * is <code>true</code> if and only if the argument is not
	 * <code>null</code> and is a <code>Float</code> object that
	 * represents a <code>float</code> with the same value as the
	 * <code>float</code> represented by this object. For this
	 * purpose, two <code>float</code> values are considered to be the
	 * same if and only if the method {@link #floatToIntBits(float)}
	 * returns the identical <code>int</code> value when applied to
	 * each.
	 * <p>
	 * Note that in most cases, for two instances of class
	 * <code>Float</code>, <code>f1</code> and <code>f2</code>, the value
	 * of <code>f1.equals(f2)</code> is <code>true</code> if and only if
	 * <blockquote><pre>
	 *   f1.floatValue() == f2.floatValue()
	 * </pre></blockquote>
	 * <p>
	 * also has the value <code>true</code>. However, there are two exceptions:
	 * <ul>
	 * <li>If <code>f1</code> and <code>f2</code> both represent
	 *     <code>Float.NaN</code>, then the <code>equals</code> method returns
	 *     <code>true</code>, even though <code>Float.NaN==Float.NaN</code>
	 *     has the value <code>false</code>.
	 * <li>If <code>f1</code> represents <code>+0.0f</code> while
	 *     <code>f2</code> represents <code>-0.0f</code>, or vice
	 *     versa, the <code>equal</code> test has the value
	 *     <code>false</code>, even though <code>0.0f==-0.0f</code>
	 *     has the value <code>true</code>.
	 * </ul>
	 * This definition allows hash tables to operate properly.
	 *
	 * @param obj the object to be compared
	 * @return  <code>true</code> if the objects are the same;
	 *          <code>false</code> otherwise.
	 * @see java.lang.Float#floatToIntBits(float)
	 */
	boolean equals(EDouble *obj);
	virtual boolean equals(EObject* obj);

	/**
	 * Compares two {@code Double} objects numerically.  There
	 * are two ways in which comparisons performed by this method
	 * differ from those performed by the Java language numerical
	 * comparison operators ({@code <, <=, ==, >=, >})
	 * when applied to primitive {@code double} values:
	 * <ul><li>
	 *          {@code Double.NaN} is considered by this method
	 *          to be equal to itself and greater than all other
	 *          {@code double} values (including
	 *          {@code Double.POSITIVE_INFINITY}).
	 * <li>
	 *          {@code 0.0d} is considered by this method to be greater
	 *          than {@code -0.0d}.
	 * </ul>
	 * This ensures that the <i>natural ordering</i> of
	 * {@code Double} objects imposed by this method is <i>consistent
	 * with equals</i>.
	 *
	 * @param   anotherDouble   the {@code Double} to be compared.
	 * @return  the value {@code 0} if {@code anotherDouble} is
	 *          numerically equal to this {@code Double}; a value
	 *          less than {@code 0} if this {@code Double}
	 *          is numerically less than {@code anotherDouble};
	 *          and a value greater than {@code 0} if this
	 *          {@code Double} is numerically greater than
	 *          {@code anotherDouble}.
	 *
	 * @since   1.2
	 */
	virtual int compareTo(EDouble* anotherDouble);

public:
	/**
	 * The value of the Double.
	 *
	 * @serial
	 */
	double value;
};

} /* namespace efc */
#endif //!EDouble_HH_
