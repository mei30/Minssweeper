#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <MinSweeper.h>
#include <GameBoard.h>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	// TODO: Must create in qml, but for sake of simplicity we use default 10X10 board
	qmlRegisterType<GameBoard>("Min", 1, 0, "GameBoard");

	QQmlApplicationEngine engine;

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
