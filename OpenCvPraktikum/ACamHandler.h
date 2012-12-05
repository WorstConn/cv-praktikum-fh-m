/*
 * CamHandler.h
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef CAMHANDLER_H_
#define CAMHANDLER_H_
#include "header.h"

class ACamHandler : public ImageSequenceInput{
private:
	/**
	 * Versucht die Standard-Webcam zu oeffnen
	 */
	virtual bool openDefWebCam()=0;
	/**
	 * Versucht die Standard-IPCam zu oeffenen
	 */
	virtual bool openDefIpCam()=0;
protected:
	const char* defaultIpCamURL;
	bool connected;
	bool ipCam;

public:

	ACamHandler();
	ACamHandler(const char* camURL);
	virtual ~ACamHandler();
	/**
	 * Oeffnet die Verbindung mit der Kamera
	 */
	virtual bool open()=0;
	/**
	 * Gibt an, ob eine Verbindung besteht
	 */
	bool isOpen();
	/**
	 * Schliesst eine bestehende Verbindung
	 */
	virtual bool close()=0;
	/**
	 * Gibt die Resourcen der des Capturers frei
	 */
	virtual bool releaseCapture()=0;
	/**
	 * Gibt das Bild des aktuellen Frames frei
	 */
	virtual bool releaseCurrentImage()=0;

	/**
	 * Gibt den aktuellen Frame als IplImage(Veraltet) zurueck
	 */
	virtual IplImage currentIplImage()=0;
	/**
	 * Gibt den aktuellen Frame als cv::Mat zurueck
	 */
	virtual cv::Mat currentMatImage()=0;

	/**
	 * Holt das naechste Bild von der Kamera
	 */
	virtual bool grabNext()=0;

	/**
	 * Versucht alle Resourcen frei zu geben
	 */
	virtual void dispose()=0;

	void setUseIpCam(bool val);

	bool useIpCam();
};

#endif /* CAMHANDLER_H_ */
