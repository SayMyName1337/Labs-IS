import os
import libgcrypt

# определение исходного файла
filename = input("text.txt: ")

# открытие файла для чтения и чтение содержимого
with open(filename, 'r') as f:
    data = f.read()

# хеширование содержимого файла с помощью алгоритма Whirlpool
whirlpool_hash = libgcrypt.hash_new(libgcrypt.ALGO_SHA512, 0)
whirlpool_hash.write(data.encode())
hash_code = whirlpool_hash.read(hash_code.get_algo_dlen())

# создание ЭЦП для хеш-кода с помощью алгоритма ГОСТ 34.10-2001
priv_key = libgcrypt.sexp_build("(genkey (rsa (nbits 4:1024)))", 0, 0)
pub_key = libgcrypt.sexp_find_token(priv_key, "public-key", 0)
signature = libgcrypt.sexp_build("(sig-val (rsa (hash sha512) (enc rsa (flags pkcs1) " + pub_key + ")))", 0, 0)
libgcrypt.sign_data(hash_code, signature, priv_key)

# добавление хеш-кода и ЭЦП в конец исходного файла
with open(filename, 'a') as f:
    f.write(f"\n\nHash code: {hash_code.hex()}")
    f.write(f"\n\nSignature:\n{libgcrypt.sexp_data(signature)}")

# вывод сообщения об отсутствии изменений в файле
print("Файл не был изменен. Содержимое файла:\n", data)

# открытие файла для записи
with open(filename, 'w') as f:
    f.write("Hello, how are you today?")

# чтение нового содержимого файла
with open(filename, 'r') as f:
    new_data = f.read()

# хеширование нового содержимого файла с помощью алгоритма Whirlpool
new_whirlpool_hash = libgcrypt.hash_new(libgcrypt.ALGO_SHA512, 0)
new_whirlpool_hash.write(new_data.encode())
new_hash_code = new_whirlpool_hash.read(new_hash_code.get_algo_dlen())

# создание новой ЭЦП для нового хеш-кода с помощью алгоритма ГОСТ 34.10-2001
libgcrypt.sign_data(new_hash_code, signature, priv_key)

# сохранение нового хеш-кода и новой ЭЦП в отдельный файл
with open("new_signature.txt", 'w') as f:
    f.write(f"New hash code: {new_hash_code.hex()}")
    f.write(f"\n\nNew signature:\n{libgcrypt.sexp_data(signature)}")

# сравнение полученных хеш-кодов и ЭЦП с записанными в конце исходного текстового файла
with open(filename, 'r') as f:
    content = f.read()
    if hash_code.hex() == content.split("Hash code: ")[1].split("\n\nSignature")[0] and \
            libgcrypt.sexp_data(signature) == content.split("Signature:\n")[1].strip():
        print("Файл не был изменен. Содержимое файла:\n", new_data)
    else:
        print("Файл был изменен.")
