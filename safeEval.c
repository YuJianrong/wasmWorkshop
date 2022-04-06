#include <emscripten.h>
#include <string.h>
#include "./quickjs/quickjs.h"

const char *EMSCRIPTEN_KEEPALIVE safeEval(const char *str)
{

  JSRuntime *runtime = JS_NewRuntime();
  JSContext *ctx = JS_NewContext(runtime);

  JSValue result = JS_Eval(ctx, str, strlen(str), "safeEval", JS_EVAL_TYPE_GLOBAL);

  if (JS_IsException(result))
  {
    JSValue realException = JS_GetException(ctx);
    return JS_ToCString(ctx, realException);
  }

  JSValue json = JS_JSONStringify(ctx, result, JS_UNDEFINED, JS_UNDEFINED);
  JS_FreeValue(ctx, result);
  const char *jsonStr = JS_ToCString(ctx, json);
  JS_FreeContext(ctx);
  JS_FreeRuntime(runtime);

  return jsonStr;
}