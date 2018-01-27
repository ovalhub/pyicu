/* ====================================================================
 * Copyright (c) 2004-2017 Open Source Applications Foundation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * ====================================================================
 */

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "measureunit.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= 0x04020000
DECLARE_CONSTANTS_TYPE(UTimeUnitFields);
#endif

/* MeasureUnit */

class t_measureunit : public _wrapper {
public:
    MeasureUnit *object;
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
static PyObject *t_measureunit_getType(t_measureunit *self);
static PyObject *t_measureunit_getSubtype(t_measureunit *self);
static PyObject *t_measureunit_getAvailable(PyTypeObject *type, PyObject *arg);
static PyObject *t_measureunit_getAvailableTypes(PyTypeObject *type);
static PyObject *t_measureunit_createAcre(PyTypeObject *type);
static PyObject *t_measureunit_createArcMinute(PyTypeObject *type);
static PyObject *t_measureunit_createArcSecond(PyTypeObject *type);
static PyObject *t_measureunit_createCelsius(PyTypeObject *type);
static PyObject *t_measureunit_createCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createCubicMile(PyTypeObject *type);
static PyObject *t_measureunit_createDay(PyTypeObject *type);
static PyObject *t_measureunit_createDegree(PyTypeObject *type);
static PyObject *t_measureunit_createFahrenheit(PyTypeObject *type);
static PyObject *t_measureunit_createFoot(PyTypeObject *type);
static PyObject *t_measureunit_createGForce(PyTypeObject *type);
static PyObject *t_measureunit_createGram(PyTypeObject *type);
static PyObject *t_measureunit_createHectare(PyTypeObject *type);
static PyObject *t_measureunit_createHectopascal(PyTypeObject *type);
static PyObject *t_measureunit_createHorsepower(PyTypeObject *type);
static PyObject *t_measureunit_createHour(PyTypeObject *type);
static PyObject *t_measureunit_createInch(PyTypeObject *type);
static PyObject *t_measureunit_createInchHg(PyTypeObject *type);
static PyObject *t_measureunit_createKilogram(PyTypeObject *type);
static PyObject *t_measureunit_createKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createKilometerPerHour(PyTypeObject *type);
static PyObject *t_measureunit_createKilowatt(PyTypeObject *type);
static PyObject *t_measureunit_createLightYear(PyTypeObject *type);
static PyObject *t_measureunit_createLiter(PyTypeObject *type);
static PyObject *t_measureunit_createMeter(PyTypeObject *type);
static PyObject *t_measureunit_createMeterPerSecond(PyTypeObject *type);
static PyObject *t_measureunit_createMile(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerHour(PyTypeObject *type);
static PyObject *t_measureunit_createMillibar(PyTypeObject *type);
static PyObject *t_measureunit_createMillimeter(PyTypeObject *type);
static PyObject *t_measureunit_createMillisecond(PyTypeObject *type);
static PyObject *t_measureunit_createMinute(PyTypeObject *type);
static PyObject *t_measureunit_createMonth(PyTypeObject *type);
static PyObject *t_measureunit_createOunce(PyTypeObject *type);
static PyObject *t_measureunit_createPicometer(PyTypeObject *type);
static PyObject *t_measureunit_createPound(PyTypeObject *type);
static PyObject *t_measureunit_createSecond(PyTypeObject *type);
static PyObject *t_measureunit_createSquareFoot(PyTypeObject *type);
static PyObject *t_measureunit_createSquareKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createSquareMeter(PyTypeObject *type);
static PyObject *t_measureunit_createSquareMile(PyTypeObject *type);
static PyObject *t_measureunit_createWatt(PyTypeObject *type);
static PyObject *t_measureunit_createWeek(PyTypeObject *type);
static PyObject *t_measureunit_createYard(PyTypeObject *type);
static PyObject *t_measureunit_createYear(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
static PyObject *t_measureunit_createAcreFoot(PyTypeObject *type);
static PyObject *t_measureunit_createAmpere(PyTypeObject *type);
static PyObject *t_measureunit_createAstronomicalUnit(PyTypeObject *type);
static PyObject *t_measureunit_createBit(PyTypeObject *type);
static PyObject *t_measureunit_createBushel(PyTypeObject *type);
static PyObject *t_measureunit_createByte(PyTypeObject *type);
static PyObject *t_measureunit_createCalorie(PyTypeObject *type);
static PyObject *t_measureunit_createCarat(PyTypeObject *type);
static PyObject *t_measureunit_createCentiliter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicFoot(PyTypeObject *type);
static PyObject *t_measureunit_createCubicInch(PyTypeObject *type);
static PyObject *t_measureunit_createCubicMeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicYard(PyTypeObject *type);
static PyObject *t_measureunit_createCup(PyTypeObject *type);
static PyObject *t_measureunit_createDeciliter(PyTypeObject *type);
static PyObject *t_measureunit_createDecimeter(PyTypeObject *type);
static PyObject *t_measureunit_createFathom(PyTypeObject *type);
static PyObject *t_measureunit_createFluidOunce(PyTypeObject *type);
static PyObject *t_measureunit_createFoodcalorie(PyTypeObject *type);
static PyObject *t_measureunit_createFurlong(PyTypeObject *type);
static PyObject *t_measureunit_createGallon(PyTypeObject *type);
static PyObject *t_measureunit_createGigabit(PyTypeObject *type);
static PyObject *t_measureunit_createGigabyte(PyTypeObject *type);
static PyObject *t_measureunit_createGigahertz(PyTypeObject *type);
static PyObject *t_measureunit_createGigawatt(PyTypeObject *type);
static PyObject *t_measureunit_createHectoliter(PyTypeObject *type);
static PyObject *t_measureunit_createHertz(PyTypeObject *type);
static PyObject *t_measureunit_createJoule(PyTypeObject *type);
static PyObject *t_measureunit_createKarat(PyTypeObject *type);
static PyObject *t_measureunit_createKelvin(PyTypeObject *type);
static PyObject *t_measureunit_createKilobit(PyTypeObject *type);
static PyObject *t_measureunit_createKilobyte(PyTypeObject *type);
static PyObject *t_measureunit_createKilocalorie(PyTypeObject *type);
static PyObject *t_measureunit_createKilohertz(PyTypeObject *type);
static PyObject *t_measureunit_createKilojoule(PyTypeObject *type);
static PyObject *t_measureunit_createKilowattHour(PyTypeObject *type);
static PyObject *t_measureunit_createLiterPerKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createLux(PyTypeObject *type);
static PyObject *t_measureunit_createMegabit(PyTypeObject *type);
static PyObject *t_measureunit_createMegabyte(PyTypeObject *type);
static PyObject *t_measureunit_createMegahertz(PyTypeObject *type);
static PyObject *t_measureunit_createMegaliter(PyTypeObject *type);
static PyObject *t_measureunit_createMegawatt(PyTypeObject *type);
static PyObject *t_measureunit_createMeterPerSecondSquared(PyTypeObject *type);
static PyObject *t_measureunit_createMetricTon(PyTypeObject *type);
static PyObject *t_measureunit_createMicrogram(PyTypeObject *type);
static PyObject *t_measureunit_createMicrometer(PyTypeObject *type);
static PyObject *t_measureunit_createMicrosecond(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerGallon(PyTypeObject *type);
static PyObject *t_measureunit_createMilliampere(PyTypeObject *type);
static PyObject *t_measureunit_createMilligram(PyTypeObject *type);
static PyObject *t_measureunit_createMilliliter(PyTypeObject *type);
static PyObject *t_measureunit_createMillimeterOfMercury(PyTypeObject *type);
static PyObject *t_measureunit_createMilliwatt(PyTypeObject *type);
static PyObject *t_measureunit_createNanometer(PyTypeObject *type);
static PyObject *t_measureunit_createNanosecond(PyTypeObject *type);
static PyObject *t_measureunit_createNauticalMile(PyTypeObject *type);
static PyObject *t_measureunit_createOhm(PyTypeObject *type);
static PyObject *t_measureunit_createOunceTroy(PyTypeObject *type);
static PyObject *t_measureunit_createParsec(PyTypeObject *type);
static PyObject *t_measureunit_createPint(PyTypeObject *type);
static PyObject *t_measureunit_createPoundPerSquareInch(PyTypeObject *type);
static PyObject *t_measureunit_createQuart(PyTypeObject *type);
static PyObject *t_measureunit_createRadian(PyTypeObject *type);
static PyObject *t_measureunit_createSquareCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createSquareInch(PyTypeObject *type);
static PyObject *t_measureunit_createSquareYard(PyTypeObject *type);
static PyObject *t_measureunit_createStone(PyTypeObject *type);
static PyObject *t_measureunit_createTablespoon(PyTypeObject *type);
static PyObject *t_measureunit_createTeaspoon(PyTypeObject *type);
static PyObject *t_measureunit_createTerabit(PyTypeObject *type);
static PyObject *t_measureunit_createTerabyte(PyTypeObject *type);
static PyObject *t_measureunit_createTon(PyTypeObject *type);
static PyObject *t_measureunit_createVolt(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
static PyObject *t_measureunit_createCentury(PyTypeObject *type);
static PyObject *t_measureunit_createCupMetric(PyTypeObject *type);
static PyObject *t_measureunit_createGenericTemperature(PyTypeObject *type);
static PyObject *t_measureunit_createKnot(PyTypeObject *type);
static PyObject *t_measureunit_createLiterPer100Kilometers(PyTypeObject *type);
static PyObject *t_measureunit_createMileScandinavian(PyTypeObject *type);
static PyObject *t_measureunit_createPintMetric(PyTypeObject *type);
static PyObject *t_measureunit_createRevolutionAngle(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)
static PyObject *t_measureunit_createGallonImperial(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerGallonImperial(PyTypeObject *type);
static PyObject *t_measureunit_createMilligramPerDeciliter(PyTypeObject *type);
static PyObject *t_measureunit_createMillimolePerLiter(PyTypeObject *type);
static PyObject *t_measureunit_createPartPerMillion(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
static PyObject *t_measureunit_createPoint(PyTypeObject *type);
#endif

static PyMethodDef t_measureunit_methods[] = {
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    DECLARE_METHOD(t_measureunit, getType, METH_NOARGS),
    DECLARE_METHOD(t_measureunit, getSubtype, METH_NOARGS),
    DECLARE_METHOD(t_measureunit, getAvailable, METH_O | METH_CLASS),
    DECLARE_METHOD(t_measureunit, getAvailableTypes, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createAcre, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createArcMinute, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createArcSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCelsius, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDay, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDegree, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFahrenheit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGForce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectare, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectopascal, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHorsepower, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createInchHg, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilogram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilometerPerHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilowatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLightYear, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeterPerSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillibar, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillisecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMinute, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMonth, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOunce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPicometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPound, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createWatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createWeek, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createYear, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    DECLARE_METHOD(t_measureunit, createAcreFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createAmpere, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createAstronomicalUnit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createBit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createBushel, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createByte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCarat, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCentiliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCup, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDeciliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDecimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFathom, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFluidOunce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFoodcalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFurlong, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGallon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigahertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigawatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectoliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createJoule, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKarat, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKelvin, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilobit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilobyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilocalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilohertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilojoule, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilowattHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiterPerKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLux, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegahertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegaliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegawatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeterPerSecondSquared, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMetricTon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrogram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrosecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerGallon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliampere, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilligram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimeterOfMercury, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliwatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNanometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNanosecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNauticalMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOhm, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOunceTroy, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createParsec, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPint, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPoundPerSquareInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createQuart, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createRadian, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createStone, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTablespoon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTeaspoon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTerabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTerabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createVolt, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
    DECLARE_METHOD(t_measureunit, createCentury, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCupMetric, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGenericTemperature, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKnot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiterPer100Kilometers, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMileScandinavian, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPintMetric, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createRevolutionAngle, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)
    DECLARE_METHOD(t_measureunit, createGallonImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerGallonImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilligramPerDeciliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimolePerLiter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPartPerMillion, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
    DECLARE_METHOD(t_measureunit, createPoint, METH_NOARGS | METH_CLASS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(MeasureUnit, t_measureunit, UObject, MeasureUnit,
             abstract_init, NULL);


/* Measure */

class t_measure : public _wrapper {
public:
    Measure *object;
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)
static int t_measure_init(t_measure *self, PyObject *args, PyObject *kwds);
#endif
static PyObject *t_measure_getNumber(t_measure *self);
static PyObject *t_measure_getUnit(t_measure *self);

static PyMethodDef t_measure_methods[] = {
    DECLARE_METHOD(t_measure, getNumber, METH_NOARGS),
    DECLARE_METHOD(t_measure, getUnit, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)
DECLARE_TYPE(Measure, t_measure, UObject, Measure, t_measure_init, NULL);
#else
DECLARE_TYPE(Measure, t_measure, UObject, Measure, abstract_init, NULL);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

/* NoUnit */

class t_nounit : public _wrapper {
public:
    NoUnit *object;
};

static PyObject *t_nounit_base(PyTypeObject *type);
static PyObject *t_nounit_percent(PyTypeObject *type);
static PyObject *t_nounit_permille(PyTypeObject *type);

static PyMethodDef t_nounit_methods[] = {
    DECLARE_METHOD(t_nounit, base, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_nounit, percent, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_nounit, permille, METH_NOARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(NoUnit, t_nounit, MeasureUnit, NoUnit,
             abstract_init, NULL);

#endif


/* CurrencyUnit */

class t_currencyunit : public _wrapper {
public:
    CurrencyUnit *object;
};

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self);

static PyMethodDef t_currencyunit_methods[] = {
    DECLARE_METHOD(t_currencyunit, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyUnit, t_currencyunit, MeasureUnit, CurrencyUnit,
             t_currencyunit_init, NULL);


/* CurrencyAmount */

class t_currencyamount : public _wrapper {
public:
    CurrencyAmount *object;
};

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_currencyamount_getCurrency(t_currencyamount *self);
static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self);

static PyMethodDef t_currencyamount_methods[] = {
    DECLARE_METHOD(t_currencyamount, getCurrency, METH_NOARGS),
    DECLARE_METHOD(t_currencyamount, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyAmount, t_currencyamount, Measure, CurrencyAmount,
             t_currencyamount_init, NULL);


/* TimeUnit */

#if U_ICU_VERSION_HEX >= 0x04020000

class t_timeunit : public _wrapper {
public:
    TimeUnit *object;
};

static PyObject *t_timeunit_getTimeUnitField(t_timeunit *self);
static PyObject *t_timeunit_createInstance(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_timeunit_methods[] = {
    DECLARE_METHOD(t_timeunit, getTimeUnitField, METH_NOARGS),
    DECLARE_METHOD(t_timeunit, createInstance, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(TimeUnit, t_timeunit, MeasureUnit, TimeUnit,
             abstract_init, NULL);


/* TimeUnitAmount */

class t_timeunitamount : public _wrapper {
public:
    TimeUnitAmount *object;
};

static int t_timeunitamount_init(t_timeunitamount *self, PyObject *args,
                                 PyObject *kwds);
static PyObject *t_timeunitamount_getUnit(t_timeunitamount *self);
static PyObject *t_timeunitamount_getTimeUnitField(t_timeunitamount *self);

static PyMethodDef t_timeunitamount_methods[] = {
    DECLARE_METHOD(t_timeunitamount, getUnit, METH_NOARGS),
    DECLARE_METHOD(t_timeunitamount, getTimeUnitField, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(TimeUnitAmount, t_timeunitamount, Measure, TimeUnitAmount,
             t_timeunitamount_init, NULL);

#endif


/* MeasureUnit */

static PyObject *t_measureunit_richcmp(t_measureunit *self,
                                       PyObject *arg, int op)
{
    int b = 0;

    switch (op) {
      case Py_EQ:
      case Py_NE:
        if (PyObject_TypeCheck(arg, &UObjectType_))
            b = *self->object == *((t_uobject *) arg)->object;
        if (op == Py_EQ)
            Py_RETURN_BOOL(b);
        Py_RETURN_BOOL(!b);
      case Py_LT:
      case Py_LE:
      case Py_GT:
      case Py_GE:
        PyErr_SetNone(PyExc_NotImplementedError);
        return NULL;
    }

    return NULL;
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

static PyObject *t_measureunit_str(t_measureunit *self)
{
    return PyString_FromString(self->object->getSubtype());
}

static PyObject *t_measureunit_getType(t_measureunit *self)
{
    return PyString_FromString(self->object->getType());
}

static PyObject *t_measureunit_getSubtype(t_measureunit *self)
{
    return PyString_FromString(self->object->getSubtype());
}

static PyObject *t_measureunit_getAvailable(PyTypeObject *type, PyObject *arg)
{
    charsArg type_name;

    if (!parseArg(arg, "n", &type_name))
    {
        UErrorCode status = U_ZERO_ERROR;
        int32_t size = MeasureUnit::getAvailable(type_name, NULL, 0, status);

        if (U_FAILURE(status))
        {
            if (status != U_BUFFER_OVERFLOW_ERROR)
                return ICUException(status).reportError();

            MeasureUnit *mus = new MeasureUnit[size];

            status = U_ZERO_ERROR;
            size = MeasureUnit::getAvailable(type_name, mus, size, status);

            if (U_FAILURE(status))
            {
                delete[] mus;
                return ICUException(status).reportError();
            }

            PyObject *result = PyTuple_New(size);

            for (int i = 0; i < size; ++i)
                PyTuple_SET_ITEM(result, i, wrap_MeasureUnit(
                    (MeasureUnit *) mus[i].clone(), T_OWNED));

            delete[] mus;

            return result;
        }
    }

    return PyErr_SetArgsError(type, "getAvailable", arg);
}

static PyObject *t_measureunit_getAvailableTypes(PyTypeObject *type)
{
    StringEnumeration *e;

    STATUS_CALL(e = MeasureUnit::getAvailableTypes(status));
    return wrap_StringEnumeration(e, T_OWNED);
}

static PyObject *t_measureunit_createAcre(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createAcre(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createArcMinute(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createArcMinute(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createArcSecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createArcSecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCelsius(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCelsius(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCentimeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCentimeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicKilometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicKilometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicMile(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicMile(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createDay(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createDay(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createDegree(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createDegree(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFahrenheit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFahrenheit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFoot(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFoot(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGForce(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGForce(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGram(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGram(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHectare(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHectare(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHectopascal(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHectopascal(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHorsepower(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHorsepower(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHour(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHour(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createInch(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createInch(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createInchHg(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createInchHg(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilogram(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilogram(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilometerPerHour(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilometerPerHour(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilowatt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilowatt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createLightYear(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createLightYear(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createLiter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createLiter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMeterPerSecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMeterPerSecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMile(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMile(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilePerHour(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilePerHour(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMillibar(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMillibar(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMillimeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMillimeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMillisecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMillisecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMinute(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMinute(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMonth(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMonth(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createOunce(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createOunce(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPicometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPicometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPound(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPound(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareFoot(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareFoot(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareKilometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareKilometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareMeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareMeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareMile(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareMile(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createWatt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createWatt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createWeek(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createWeek(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createYard(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createYard(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createYear(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createYear(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)

static PyObject *t_measureunit_createAcreFoot(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createAcreFoot(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createAmpere(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createAmpere(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createAstronomicalUnit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createAstronomicalUnit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createBit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createBit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createBushel(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createBushel(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createByte(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createByte(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCalorie(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCalorie(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCarat(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCarat(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCentiliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCentiliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicCentimeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicCentimeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicFoot(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicFoot(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicInch(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicInch(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicMeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicMeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCubicYard(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCubicYard(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCup(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCup(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createDeciliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createDeciliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createDecimeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createDecimeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFathom(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFathom(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFluidOunce(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFluidOunce(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFoodcalorie(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFoodcalorie(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createFurlong(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createFurlong(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGallon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGallon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGigabit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGigabit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGigabyte(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGigabyte(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGigahertz(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGigahertz(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGigawatt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGigawatt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHectoliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHectoliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createHertz(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createHertz(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createJoule(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createJoule(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKarat(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKarat(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKelvin(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKelvin(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilobit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilobit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilobyte(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilobyte(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilocalorie(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilocalorie(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilohertz(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilohertz(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilojoule(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilojoule(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKilowattHour(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKilowattHour(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createLiterPerKilometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createLiterPerKilometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createLux(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createLux(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMegabit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMegabit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMegabyte(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMegabyte(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMegahertz(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMegahertz(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMegaliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMegaliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMegawatt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMegawatt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMeterPerSecondSquared(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMeterPerSecondSquared(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMetricTon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMetricTon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMicrogram(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMicrogram(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMicrometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMicrometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMicrosecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMicrosecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilePerGallon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilePerGallon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilliampere(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilliampere(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilligram(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilligram(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilliliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilliliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMillimeterOfMercury(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMillimeterOfMercury(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilliwatt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilliwatt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createNanometer(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createNanometer(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createNanosecond(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createNanosecond(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createNauticalMile(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createNauticalMile(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createOhm(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createOhm(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createOunceTroy(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createOunceTroy(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createParsec(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createParsec(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPint(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPint(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPoundPerSquareInch(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPoundPerSquareInch(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createQuart(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createQuart(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createRadian(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createRadian(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareCentimeter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareCentimeter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareInch(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareInch(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createSquareYard(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createSquareYard(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createStone(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createStone(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createTablespoon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createTablespoon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createTeaspoon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createTeaspoon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createTerabit(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createTerabit(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createTerabyte(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createTerabyte(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createTon(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createTon(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createVolt(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createVolt(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)

static PyObject *t_measureunit_createCentury(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCentury(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createCupMetric(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createCupMetric(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createGenericTemperature(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGenericTemperature(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createKnot(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createKnot(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createLiterPer100Kilometers(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createLiterPer100Kilometers(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMileScandinavian(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMileScandinavian(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPintMetric(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPintMetric(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createRevolutionAngle(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createRevolutionAngle(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)

static PyObject *t_measureunit_createGallonImperial(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createGallonImperial(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilePerGallonImperial(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilePerGallonImperial(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMilligramPerDeciliter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMilligramPerDeciliter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createMillimolePerLiter(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createMillimolePerLiter(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

static PyObject *t_measureunit_createPartPerMillion(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPartPerMillion(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)

static PyObject *t_measureunit_createPoint(PyTypeObject *type)
{
    MeasureUnit *mu;
    STATUS_CALL(mu = MeasureUnit::createPoint(status));

    return wrap_MeasureUnit(mu, T_OWNED);
}

#endif


/* Measure */

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)

static int t_measure_init(t_measure *self, PyObject *args, PyObject *kwds)
{
    Formattable *number;
    MeasureUnit *unit;
    double d;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "dP", TYPE_ID(MeasureUnit), &d, &unit))
        {
            INT_STATUS_CALL(self->object = new Measure(
                Formattable(d), (MeasureUnit *) unit->clone(), status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "PP", TYPE_CLASSID(Formattable),
                       TYPE_ID(MeasureUnit), &number, &unit))
        {
            INT_STATUS_CALL(self->object = new Measure(
                *number, (MeasureUnit *) unit->clone(), status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

#endif

static PyObject *t_measure_getNumber(t_measure *self)
{
    Formattable *f = new Formattable(self->object->getNumber());
    return wrap_Formattable(f, T_OWNED);
}

static PyObject *t_measure_getUnit(t_measure *self)
{
    MeasureUnit *u = (MeasureUnit *) self->object->getUnit().clone();
    return wrap_MeasureUnit(u, T_OWNED);
}

static PyObject *t_measure_str(t_measure *self)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
    UnicodeString u;

    STATUS_CALL(u = icu::number::NumberFormatter::withLocale(
        Locale::getDefault())
                .unit(self->object->getUnit())
                .unitWidth(UNumberUnitWidth::UNUM_UNIT_WIDTH_FULL_NAME)
                .formatDouble(self->object->getNumber().getDouble(), status)
                .toString());

    return PyUnicode_FromUnicodeString(&u);
#else
    PyObject *value = wrap_Formattable(const_cast<Formattable *>(&self->object->getNumber()), 0);
    PyObject *unit = wrap_MeasureUnit(const_cast<MeasureUnit *>(&self->object->getUnit()), 0);
    PyObject *v_str = PyObject_Str(value);
    PyObject *u_str = PyObject_Str(unit);
    PyObject *args = PyTuple_Pack(2, v_str, u_str);
    PyObject *format = PyString_FromString("%s %s");
    PyObject *str = PyString_Format(format, args);

    Py_DECREF(format);
    Py_DECREF(args);
    Py_DECREF(u_str);
    Py_DECREF(v_str);
    Py_DECREF(unit);
    Py_DECREF(value);

    return str;
#endif
}

static PyObject *t_measure_richcmp(t_measure *self, PyObject *arg, int op)
{
    int b = 0;

    switch (op) {
      case Py_EQ:
      case Py_NE:
        if (PyObject_TypeCheck(arg, &UObjectType_))
            b = *self->object == *((t_uobject *) arg)->object;
        if (op == Py_EQ)
            Py_RETURN_BOOL(b);
        Py_RETURN_BOOL(!b);
      case Py_LT:
      case Py_LE:
      case Py_GT:
      case Py_GE:
        PyErr_SetNone(PyExc_NotImplementedError);
        return NULL;
    }

    return NULL;
}


/* NoUnit */

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

static PyObject *t_nounit_base(PyTypeObject *type)
{
  return wrap_NoUnit((NoUnit *) NoUnit::base().clone(), T_OWNED);
}

static PyObject *t_nounit_percent(PyTypeObject *type)
{
    return wrap_NoUnit((NoUnit *) NoUnit::percent().clone(), T_OWNED);
}

static PyObject *t_nounit_permille(PyTypeObject *type)
{
    return wrap_NoUnit((NoUnit *) NoUnit::permille().clone(), T_OWNED);
}

#endif


/* CurrencyUnit */

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        CurrencyUnit *cu = new CurrencyUnit(u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = cu;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyunit_str(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}


/* CurrencyAmount */

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    Formattable *f;
    double d;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "PS", TYPE_CLASSID(Formattable),
                   &f, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(*f, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    if (!parseArgs(args, "dS", &d, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(d, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyamount_getCurrency(t_currencyamount *self)
{
    CurrencyUnit *cu = new CurrencyUnit(self->object->getCurrency());
    return wrap_CurrencyUnit(cu, T_OWNED);
}

static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyamount_str(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    UErrorCode status = U_ZERO_ERROR;
    double d = self->object->getNumber().getDouble(status);

    PyObject *currency = PyUnicode_FromUnicodeString(&u);
    PyObject *amount = PyFloat_FromDouble(d);
    PyObject *format = PyString_FromString("%s %0.2f");
    PyObject *tuple = PyTuple_New(2);
    PyObject *str;

    PyTuple_SET_ITEM(tuple, 0, currency);
    PyTuple_SET_ITEM(tuple, 1, amount);
    str = PyString_Format(format, tuple);
    Py_DECREF(tuple);
    Py_DECREF(format);

    return str;
}


/* TimeUnit */

#if U_ICU_VERSION_HEX >= 0x04020000

static PyObject *t_timeunit_getTimeUnitField(t_timeunit *self)
{
    return PyInt_FromLong(self->object->getTimeUnitField());
}

static PyObject *t_timeunit_createInstance(PyTypeObject *type, PyObject *arg)
{
    TimeUnit::UTimeUnitFields field;

    if (!parseArg(arg, "i", &field))
    {
        TimeUnit *tu;
        STATUS_CALL(tu = TimeUnit::createInstance(field, status));

        return wrap_TimeUnit(tu, T_OWNED);
    }

    return PyErr_SetArgsError(type, "getAvailable", arg);
}


/* TimeUnitAmount */

static int t_timeunitamount_init(t_timeunitamount *self, PyObject *args,
                                 PyObject *kwds)
{
    Formattable *obj;
    TimeUnit::UTimeUnitFields field;
    double d;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Pi", TYPE_CLASSID(Formattable), &obj, &field))
        {
            INT_STATUS_CALL(self->object = new TimeUnitAmount(
                *obj, field, status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "di", &d, &field))
        {
            INT_STATUS_CALL(self->object = new TimeUnitAmount(
                d, field, status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_timeunitamount_getUnit(t_timeunitamount *self)
{
    return wrap_TimeUnit(
        (TimeUnit *) self->object->getTimeUnit().clone(), T_OWNED);
}

static PyObject *t_timeunitamount_getTimeUnitField(t_timeunitamount *self)
{
    return PyInt_FromLong(self->object->getTimeUnitField());
}

#endif

void _init_measureunit(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    MeasureUnitType_.tp_str = (reprfunc) t_measureunit_str;
#endif
    MeasureUnitType_.tp_richcompare = (richcmpfunc) t_measureunit_richcmp;
    MeasureType_.tp_richcompare = (richcmpfunc) t_measure_richcmp;
    CurrencyUnitType_.tp_str = (reprfunc) t_currencyunit_str;
    CurrencyAmountType_.tp_str = (reprfunc) t_currencyamount_str;
    MeasureType_.tp_str = (reprfunc) t_measure_str;

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_CONSTANTS_TYPE(UTimeUnitFields, m);
#endif

    INSTALL_TYPE(MeasureUnit, m);
    INSTALL_TYPE(Measure, m);
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
    REGISTER_TYPE(NoUnit, m);
#endif
    REGISTER_TYPE(CurrencyUnit, m);
    REGISTER_TYPE(CurrencyAmount, m);
#if U_ICU_VERSION_HEX >= 0x04020000
    REGISTER_TYPE(TimeUnit, m);
    REGISTER_TYPE(TimeUnitAmount, m);
#endif

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_ENUM(UTimeUnitFields, "YEAR", TimeUnit::UTIMEUNIT_YEAR);
    INSTALL_ENUM(UTimeUnitFields, "MONTH", TimeUnit::UTIMEUNIT_MONTH);
    INSTALL_ENUM(UTimeUnitFields, "DAY", TimeUnit::UTIMEUNIT_DAY);
    INSTALL_ENUM(UTimeUnitFields, "WEEK", TimeUnit::UTIMEUNIT_WEEK);
    INSTALL_ENUM(UTimeUnitFields, "HOUR", TimeUnit::UTIMEUNIT_HOUR);
    INSTALL_ENUM(UTimeUnitFields, "MINUTE", TimeUnit::UTIMEUNIT_MINUTE);
    INSTALL_ENUM(UTimeUnitFields, "SECOND", TimeUnit::UTIMEUNIT_SECOND);
#endif
}
