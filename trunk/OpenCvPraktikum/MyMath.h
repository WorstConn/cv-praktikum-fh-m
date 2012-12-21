/*
 * Math.h
 *
 *  Created on: 10.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef MATH_H_
#define MATH_H_
using namespace std;
using namespace cv;

class MyMath {
public:
    MyMath();
    virtual ~MyMath();

    static int ggtRek(int x, int y);
    static int ggtIt(int x, int y);

    /**
     * Prueft, ob sich ein bestimmter Wert in einem Toleranzbereich von +/- 'percent'% 
     * @param val der Wert
     * @param  ref der Referenzwert, mit dem geprueft wird
     * @param   percent toleranzbereich in % den der Wert von <b>val</b> gegen&uuml;ber dem von <b>ref</b> abweichen darf.
     * @return true, falls val in der n&auml;he von ref liegt
     */
    static bool inRange(unsigned int val, unsigned int ref, unsigned int percent);

    /**
     * Absolut Betrag
     * @param value Eingabewert
     * @return den Betrag des Eingabewertes
     */
    static float abs(float value);
    /**
     * Absolut Betrag
     * @param value Eingabewert
     * @return der Betrag des Eingabewertes
     */
    static int abs(int value);
    /**
     * Absolut Wert 
     * @param value Eingabewert
     * @return x:={x &isin; R | x >= 0 } 
     */
    static double abs(double value);

    /**
     * 'Groesser als' fuer Rects
     * @param a 
     * @param b
     * @return true, wenn a>b sonst false 
     */
    static bool biggerThan(Rect a, Rect b);

    /**
     * Distanz zwischen zwei Punkten.
     * @param pFrom Punkt 1
     * @param pTo Punkt 2
     * @return die Distanz
     */
    static float dist(Point3f pFrom, Point3f pTo);

    /**
     * Distanz zwischen zwei Punkten.
     * @param pFrom Punkt 1
     * @param pTo Punkt 2
     * @return die Distanz
     */
    static float dist(Point2i pFrom, Point2i pTo);
    /**
     * Gibt an, ob sich ein Punkt innerhalb oder ausserhalb eines Keises,<br>
     * gegeben durch <code>center</code> und <code>radius</code>, befindet.
     * @param center Zentrum des Kreises
     * @param radius Radius des Kreises
     * @param examine der Punkt, der Untersucht werden soll.
     * @return 
     */
    static bool isInCircle(Point2i center, int radius, Point2i examine);

    static Point3i RectToCircle(Rect r);


    static Point2i RectCenter(Rect r);

    static int RectRadius(Rect rect);

};

#endif /* MATH_H_ */
