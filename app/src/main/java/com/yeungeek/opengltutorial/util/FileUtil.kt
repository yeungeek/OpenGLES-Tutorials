package com.yeungeek.opengltutorial.util

import android.content.Context
import android.content.res.AssetManager
import android.util.Log
import java.io.File
import java.io.RandomAccessFile

/**
 *  Created by jian.yang on 2023/10/6.
 */
object FileUtil {

    fun copyAssetsToPrivate(context: Context) {
        val destinationPath = context.filesDir.path
        val am = context.assets
        copyAssetsToPrivate(am, "datas", destinationPath)
    }

    private fun copyAssetsToPrivate(
        am: AssetManager,
        sourcePath: String,
        destinationPath: String
    ) {
        val separator = File.separator;

        try {
            val files = am.list(sourcePath) ?: return
            if (files.isNotEmpty()) {
                val destinationFile = File(destinationPath)
                if (!destinationFile.exists() && !destinationFile.mkdirs()) {
                    return
                }

                Log.d("FileUtil", "###### $sourcePath is directory")
                for (filename in files) {
                    copyAssetsToPrivate(
                        am, sourcePath.plus(separator).plus(filename),
                        destinationPath.plus(separator).plus(filename)
                    )
                }
            } else {
                Log.d("FileUtil", "###### $sourcePath is file")
                if (!fileExists(destinationPath)) {
                    extractAsset(am, sourcePath, destinationPath)
                }
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    private fun extractAsset(am: AssetManager, assetFilePath: String, destinationFilePath: String) {
        Log.d("FileUtil", "###### extra asset $assetFilePath to $destinationFilePath")
        val randomAccessFile = RandomAccessFile(destinationFilePath, "rw")
        val inputStream = am.open(assetFilePath)
        val buffer = ByteArray(1024)

        var read: Int
        while (inputStream.read(buffer).also { read = it } != -1) {
            randomAccessFile.write(buffer, 0, read)
        }

        inputStream.close()
        randomAccessFile.close()
    }

    private fun fileExists(filePath: String): Boolean {
        val file = File(filePath)
        return file.exists()
    }
}