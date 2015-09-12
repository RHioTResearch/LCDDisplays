#include "org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544.h"
#include "MiniLcdPCD8544.h"
#include <memory>

static unique_ptr<MiniLcdPCD8544> theLCD;

/**
 * The shared library load callback to set the JavaVM pointer
 */
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    printf("JNI_OnLoad, requesting JNI_VERSION_1_8\n");
    return JNI_VERSION_1_8;
}

/*
 * Class:     org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544
 * Method:    doInit
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544_doInit
        (JNIEnv *env, jobject lcd, jint rows, jint cols) {
    MiniLcdPCD8544* ptr = MiniLcdPCD8544::getLcdDisplayInstance();
    theLCD.reset(ptr);
    return theLCD->init(rows, cols);
}

/*
 * Class:     org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544
 * Method:    doClear
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544_doClear
        (JNIEnv *env, jobject lcd) {
    theLCD->clear();
    return 0;
}

static void getJStringContent(JNIEnv *env, jstring javaText, std::string &ctext) {
    if (!javaText) {
        ctext.clear();
        return;
    }

    const char *s = env->GetStringUTFChars(javaText, nullptr);
    ctext = s;
    env->ReleaseStringUTFChars(javaText,s);
}

/*
 * Class:     org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544
 * Method:    doText
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544_doText
        (JNIEnv *env, jobject lcd, jstring text, jint col, jint row) {

    string ctext;
    getJStringContent(env, text, ctext);
    theLCD->displayText(ctext, col, row);
    return 0;
}
