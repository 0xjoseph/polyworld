#include "SceneMonitorView.h"

#include "AgentTracker.h"
#include "CameraController.h"
#include "Monitor.h"
#include "SceneRenderer.h"

//===========================================================================
// SceneMonitorView
//===========================================================================

//---------------------------------------------------------------------------
// SceneMonitorView::SceneMonitorView
//---------------------------------------------------------------------------
SceneMonitorView::SceneMonitorView( SceneMonitor *monitor )
	: MonitorView( monitor,
				   monitor->getRenderer()->getBufferWidth(),
				   monitor->getRenderer()->getBufferHeight(),
				   false)
	, renderer( monitor->getRenderer()  )
	, cameraController( monitor->getCameraController() )
{
	setTracker( cameraController->getAgentTracker() );
}

//---------------------------------------------------------------------------
// SceneMonitorView::~SceneMonitorView
//---------------------------------------------------------------------------
SceneMonitorView::~SceneMonitorView()
{
}

//---------------------------------------------------------------------------
// SceneMonitorView::showEvent
//---------------------------------------------------------------------------
void SceneMonitorView::showEvent( QShowEvent *event )
{
    draw_handle =
        renderer->renderComplete += [=]() {this->draw();};

	QGLWidget::showEvent( event );
}

//---------------------------------------------------------------------------
// SceneMonitorView::hideEvent
//---------------------------------------------------------------------------
void SceneMonitorView::hideEvent( QHideEvent *event )
{
    renderer->renderComplete -= draw_handle;

	QGLWidget::hideEvent( event );
}

//---------------------------------------------------------------------------
// SceneMonitorView::paintGL
//---------------------------------------------------------------------------
void SceneMonitorView::paintGL()
{
	draw();
}

//---------------------------------------------------------------------------
// SceneMonitorView::draw
//---------------------------------------------------------------------------
void SceneMonitorView::draw()
{
	renderer->copyTo( this );
}

//---------------------------------------------------------------------------
// SceneMonitorView::setTracker
//---------------------------------------------------------------------------
void SceneMonitorView::setTracker( AgentTracker *tracker )
{
	if( tracker )
	{
        tracker->targetChanged += [=](AgentTracker *tracker) {this->updateTarget(tracker);};

		updateTarget( tracker );
	}
}

//---------------------------------------------------------------------------
// SceneMonitorView::updateTarget
//---------------------------------------------------------------------------
void SceneMonitorView::updateTarget( AgentTracker *tracker )
{
	if( tracker )
	{
		char title[128];
		sprintf( title, "%s (%s)", getMonitor()->getTitle(), tracker->getStateTitle().c_str() );

		setWindowTitle( title );
	}
	else
	{
		setWindowTitle( getMonitor()->getTitle() );
	}
}
