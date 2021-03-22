package org.ryochan7.dcnow;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.NotificationChannel;
import android.content.Context;

public class NotificationClient
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;

    public NotificationClient()
    {
    }

    public static void notify(Context context, String summary, String body)
    {
        try {
            m_notificationManager = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel notificationChannel = new NotificationChannel("DCNow", "Dreamcast Now", importance);
            m_notificationManager.createNotificationChannel(notificationChannel);

            m_builder = new Notification.Builder(context, notificationChannel.getId());
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle(summary);

            m_builder.setContentText(body);
            m_notificationManager.notify(0, m_builder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
