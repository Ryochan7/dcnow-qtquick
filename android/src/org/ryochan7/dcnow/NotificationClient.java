package org.ryochan7.dcnow;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import org.qtproject.qt5.android.bindings.QtActivity;

public class NotificationClient extends QtActivity
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;

    public NotificationClient()
    {
        m_instance = this;
    }

    public static void notify(String summary, String body)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle(summary);
        }

        m_builder.setContentText(body);
        m_notificationManager.notify(1, m_builder.build());
    }
}
