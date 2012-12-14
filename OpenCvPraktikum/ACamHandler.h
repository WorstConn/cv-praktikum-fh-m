/*
 * CamHandler.h
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef CAMHANDLER_H_
#define CAMHANDLER_H_
#include "header.h"

/**
 * Hilft bei der Spezifikation des Aufnahmebildes
 */
enum INPUT_FORMAT {
    rNULL, rUnknown, r480p, r720p, r1080p
};

class ACamHandler : public ImageSequenceInput {
private:
    /**
     * Versucht die Standard-Webcam zu oeffnen
     */
    virtual bool openDefWebCam() = 0;
    /**
     * Versucht die Standard-IPCam zu oeffenen
     */
    virtual bool openDefIpCam() = 0;
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
    virtual bool open() = 0;
    /**
     * Gibt an, ob eine Verbindung besteht
     */
    bool isOpen();
    /**
     * Schliesst eine bestehende Verbindung
     */
    virtual bool close() = 0;
    /**
     * Gibt die Resourcen der des Capturers frei
     */
    virtual bool releaseCapture() = 0;
    /**
     * Gibt das Bild des aktuellen Frames frei
     */
    virtual bool releaseCurrentImage() = 0;

    /**
     * Gibt den aktuellen Frame als IplImage(Veraltet) zurueck
     */
    virtual IplImage currentIplImage() = 0;
    /**
     * Gibt den aktuellen Frame als cv::Mat zurueck
     */
    virtual cv::Mat currentMatImage() = 0;

    /**
     * Holt das naechste Bild von der Kamera
     */
    virtual bool grabNext() = 0;

    /**
     * Versucht alle Resourcen frei zu geben
     */
    virtual void dispose() = 0;

    /**
     * Legt fest, ob eine IP-Cam verwendet werden soll.
     * @param val
     */
    void setUseIpCam(bool val);

    /**
     * Gibt an, ob eine IP-Cam verwendet wird.
     * @return <code>true</code>, wenn versucht wird, eine IP-Cam zu verwenden. Sonst <code>false</code>
     */
    bool useIpCam();

    /**
     * Versucht eine Andere Bildgr&ouml;&szlig;e von der Kamera anzufordern.
     * @param newResolution Die Aufl&ouml;sung, die von der Kamera angefordert wird.
     * @return <code>true</code>, wenn die &Auml;nderung angenommen wurden, sonst <code>false</code>.
     */
    virtual bool requestFormat(INPUT_FORMAT newResolution) = 0;

    /**
     * Gibt die aktuelle <code>RESOLUTION</code> des Kamerabildes zur&uuml;ck.
     * @return die aktuelle <code>RESOLUTION</code>.
     */
    virtual INPUT_FORMAT currentCamInputFormat() = 0;
};

#endif /* CAMHANDLER_H_ */
