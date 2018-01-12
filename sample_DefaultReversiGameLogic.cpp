#include "sample_DefaultReversiGameLogic.h"
#include "include/Board.h"
#include "include/GameLogic.h"
#include "include/DefaultLogic.h"

class ArrayInfo {
private:
    int size;
    int ** data;

public:
    void SetData(int** data) {
        this->data = data;
    }
    void SetSize(int size) {
        this->size = size;
    }

    int ** GetData() {
        return data;
    }
    int GetSize() {
        return size;
    }
};

ArrayInfo TwoDimentionalArrayFromjobjectArray(JNIEnv * env, jobjectArray array);
boardContent ** CastIntArrayToBoardTypeArray (ArrayInfo arrayInfo);
jobjectArray TwoDimentionalArrayTojobjectArray (JNIEnv * env, ArrayInfo arrayInfo);

static jfieldID _get_self_id(JNIEnv *env, jobject thisObj) {
    static int init = 0;
    static jfieldID fidSelfPtr;
    if(!init)
    {
        jclass thisClass = env->GetObjectClass(thisObj);
        fidSelfPtr = env->GetFieldID(thisClass, "self_ptr", "J");
    }
    return fidSelfPtr;
}

static GameLogic *_get_self(JNIEnv *env, jobject thisObj) {
    jlong selfPtr = env->GetLongField(thisObj, _get_self_id(env, thisObj));
    return *(GameLogic**)&selfPtr;
}

static void _set_self(JNIEnv *env, jobject thisObj, GameLogic *self){
    jlong selfPtr = *(jlong*)&self;
    env->SetLongField(thisObj, _get_self_id(env, thisObj), selfPtr);
}


JNIEXPORT void JNICALL Java_sample_DefaultReversiGameLogic_initialize
  (JNIEnv * env, jobject thisObj)  {
    GameLogic* logic = new DefaultLogic();
    _set_self(env, thisObj, logic);

}

JNIEXPORT void JNICALL Java_sample_DefaultReversiGameLogic_CheckPossibleMoves
  (JNIEnv *env, jobject thisObj, jobjectArray array, jint player){
    ArrayInfo twoDimArrayInfo = TwoDimentionalArrayFromjobjectArray(env, array);
    boardContent ** content = CastIntArrayToBoardTypeArray(twoDimArrayInfo);

    Board board (content);

    GameLogic * logic = _get_self(env, thisObj);


    logic->CheckPossibleMoves(&board, static_cast<playerIdentifier > (player));
}


JNIEXPORT jobjectArray JNICALL Java_sample_DefaultReversiGameLogic_UpdateBoard
  (JNIEnv *env, jobject thisObj, jobjectArray array, jint row, jint col, jint playerSymbol){

    ArrayInfo twoDimArrayInfo = TwoDimentionalArrayFromjobjectArray(env, array);
    boardContent ** content = CastIntArrayToBoardTypeArray(twoDimArrayInfo);

    Board board (content);

    GameLogic * logic = _get_self(env, thisObj);

    logic->UpdateBoard(&board, row, col, static_cast<boardContent > (playerSymbol));


    return TwoDimentionalArrayTojobjectArray(env, twoDimArrayInfo);

}


JNIEXPORT jboolean JNICALL Java_sample_DefaultReversiGameLogic_CheckLocation
  (JNIEnv *env, jobject thisObj, jint row, jint col){

    GameLogic * logic = _get_self(env, thisObj);
    return (jboolean)logic->IsLocationValid(Cell(row, col));
}


JNIEXPORT jboolean JNICALL Java_sample_DefaultReversiGameLogic_IsGameOver
  (JNIEnv *env, jobject thisObj, jobjectArray array){

    ArrayInfo twoDimArrayInfo = TwoDimentionalArrayFromjobjectArray(env, array);
    boardContent ** content = CastIntArrayToBoardTypeArray(twoDimArrayInfo);

    Board board (content);

    GameLogic * logic = _get_self(env, thisObj);
    return (jboolean)logic->IsGameOver(&board);
}


JNIEXPORT jint JNICALL Java_sample_DefaultReversiGameLogic_DeclareWinner
  (JNIEnv *env, jobject thisObj, jobjectArray array){
    ArrayInfo twoDimArrayInfo = TwoDimentionalArrayFromjobjectArray(env, array);
    boardContent ** content = CastIntArrayToBoardTypeArray(twoDimArrayInfo);

    Board board (content);

    GameLogic * logic = _get_self(env, thisObj);
    return static_cast<int >(logic->DeclareWinner(&board));
}


JNIEXPORT jboolean JNICALL Java_sample_DefaultReversiGameLogic_IsPossibleMoveExist
        (JNIEnv * env, jobject thisObj) {
    GameLogic * logic = _get_self(env, thisObj);
    return (jboolean)logic->GetMoves().empty();
}

JNIEXPORT void JNICALL Java_sample_DefaultReversiGameLogic_destroy
  (JNIEnv * env, jobject thisObj){
    GameLogic * logic = _get_self(env, thisObj);
    delete logic;
}

ArrayInfo TwoDimentionalArrayFromjobjectArray(JNIEnv * env, jobjectArray array) {
    int len1 = env -> GetArrayLength(array);
    jintArray dim=  (jintArray)env->GetObjectArrayElement(array, 0);
    int len2 = env -> GetArrayLength(dim);
    int **localArray;
    // allocate localArray using len1
    localArray = new int*[len1];
    for(int i=0; i<len1; ++i){
        jintArray oneDim= (jintArray)env->GetObjectArrayElement(array, i);
        //need to check this line
        jint * element = env->GetIntArrayElements(oneDim, 0);
        //allocate localArray[i] using len2
        localArray[i] = new int[len2];
        for(int j=0; j<len2; ++j) {
            localArray[i][j]= element[j];
        }
    }

    ArrayInfo arrayInfo;
    arrayInfo.SetData(localArray);
    arrayInfo.SetSize(len1);

    return arrayInfo;
}

boardContent ** CastIntArrayToBoardTypeArray (ArrayInfo arrayInfo) {
    boardContent ** content;
    content = new boardContent*[NUM_OF_ROWS];
    for(int i = 0; i < NUM_OF_ROWS; ++i)
        content[i] = new boardContent[NUM_OF_COLS];


    for (int i = 0; i < arrayInfo.GetSize(); i++) {
        for (int j = 0; j < arrayInfo.GetSize(); j++) {
            content[i][j] = static_cast<boardContent >(arrayInfo.GetData()[i][j]);
        }
    }
}

jobjectArray TwoDimentionalArrayTojobjectArray (JNIEnv * env, ArrayInfo arrayInfo) {
    // Get the int array class
    jclass cls = env->FindClass("[I");

    jintArray iniVal = env->NewIntArray(arrayInfo.GetSize());
    // Create the returnable jobjectArray with an initial value
    jobjectArray outer = env->NewObjectArray(arrayInfo.GetSize(),cls, iniVal);

    for (int i = 0; i < arrayInfo.GetSize(); i++)
    {
        jintArray inner = env->NewIntArray(arrayInfo.GetSize());
        env->SetIntArrayRegion(inner, 0, arrayInfo.GetSize(), arrayInfo.GetData()[i]);
        // set inner's values
        env->SetObjectArrayElement(outer, i, inner);
        env->DeleteLocalRef(inner);
    }
    return outer;
}



