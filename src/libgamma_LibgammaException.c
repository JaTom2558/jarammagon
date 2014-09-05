/**
 * jlibgamma -- Display server abstraction layer for gamma ramp and Java
 * Copyright (C) 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "libgamma_LibgammaException.h"

#include <stdlib.h>
#include <string.h>

#include <libgamma.h>


#define J  JNIEnv* env, jclass class



/**
 * Returns the name of the definition associated with
 * a <tt>libgamma</tt> error code.
 * 
 * @param   value  The error code.
 * @return         The name of the definition associated with the error code,
 *                 {@code null} if the error code does not exist.
 */
jstring Java_libgamma_LibgammaException_name_1of_1error(J, jint value)
{
  /* It is really unlikely that `malloc` returns `NULL` here
   * and error handing makes this unnecessarily comples,
   * therefore we will simply skip it. */
  
  const char* do_not_free_this = libgamma_name_of_error(value);
  char* this_will_be_freed;
  size_t n;
  if (do_not_free_this == NULL)
    return NULL;
  
  n = strlen(do_not_free_this) + 1;
  this_will_be_freed = malloc(n * sizeof(char));
  memcpy(this_will_be_freed, do_not_free_this, n * sizeof(char));
  
  return (*env)->NewStringUTF(env, this_will_be_freed);
  (void) class;
}


/**
 * Return the value of a <tt>libgamma</tt> error definition
 * refered to by name.
 * 
 * @param   name  The name of the definition associated with the error code.
 * @return        The error code, zero if the name is {@code null}
 *                or does not refer to a <tt>libgamma</tt> error.
 */
jint Java_libgamma_LibgammaException_value_1of_1error(J, jstring name)
{
  const char* name_chars;
  int rc;
  if (name == NULL)
    return 0;
  name_chars = (*env)->GetStringUTFChars(env, name, NULL);
  rc = libgamma_value_of_error(name_chars);
  (*env)->ReleaseStringUTFChars(env, name, name_chars);
  return rc;
  (void) class;
}


/**
 * Acquire the value that should go to {@link #group_gid}.
 * 
 * @return  The value that should go to {@link #group_gid}.
 */
jint Java_libgamma_LibgammaException_libgamma_1group_1gid(J)
{
  return libgamma_group_gid;
  (void) env;
  (void) class;
}


/**
 * Acquire the value that should go to {@link #group_name}.
 * 
 * @return  The value that should go to {@link #group_name}.
 */
jstring Java_libgamma_LibgammaException_libgamma_1group_1name(J)
{
  /* It is really unlikely that `malloc` returns `NULL` here
   * and error handing makes this unnecessarily comples,
   * therefore we will simply skip it. */
  
  const char* do_not_free_this = libgamma_group_name;
  char* this_will_be_freed;
  size_t n;
  if (do_not_free_this == NULL)
    return NULL;
  
  n = strlen(do_not_free_this) + 1;
  this_will_be_freed = malloc(n * sizeof(char));
  memcpy(this_will_be_freed, do_not_free_this, n * sizeof(char));
  
  return (*env)->NewStringUTF(env, this_will_be_freed);
  (void) class;
}


/**
 * Get a textual description of a system error code.
 * 
 * @param   error_code  The error code.
 * @return              A textual description of the error code.
 */
jstring Java_libgamma_LibgammaException_strerror(J, jint error_code)
{
  /* It is really unlikely that `malloc` returns `NULL` here
   * and error handing makes this unnecessarily comples,
   * therefore we will simply skip it. */
  
  const char* do_not_free_this = strerror(error_code);
  char* this_will_be_freed;
  size_t n;
  if (do_not_free_this == NULL)
    return NULL;
  
  n = strlen(do_not_free_this) + 1;
  this_will_be_freed = malloc(n * sizeof(char));
  memcpy(this_will_be_freed, do_not_free_this, n * sizeof(char));
  
  return (*env)->NewStringUTF(env, this_will_be_freed);
  (void) class;
}

